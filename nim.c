#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int misere = 1;

struct move
{
  int heap;
  int nb;
};

static int
heaps_xor (int *heaps, int nb_heaps)
{
  int sum = 0;
  for (int i = 0; i < nb_heaps; i++)
    sum ^= heaps[i];
  return sum;
}

static int
heaps_max (int *heaps, int nb_heaps)
{
  int max = 0;
  for (int i = 0; i < nb_heaps; i++)
    if (heaps[i] > max)
      max = heaps[i];
  return max;
}

static int
heaps_non_empty (int *heaps, int nb_heaps)
{
  int non_empty = 0;
  for (int i = 0; i < nb_heaps; i++)
    if (heaps[i])
      non_empty++;
  return non_empty;
}

static struct move
heaps_best_move (int *heaps, int nb_heaps)
{
  int heap = rand () % nb_heaps;
  int nb_elements = 0;
  int xor = heaps_xor (heaps, nb_heaps);
  if (!xor)
  {
    int i = 0;
    for (i = 0; i < nb_heaps && !heaps[(heap + i) % nb_heaps]; i++);
    heap = (heap + i) % nb_heaps;
    nb_elements = rand () % heaps[heap] + 1;
    if (heaps_max (heaps, nb_heaps) <= 1 && nb_elements > 1)
      nb_elements--;
  }
  else
  {
    int i = 0;
    for (i = 0; i < nb_heaps && (xor ^ heaps[(heap + i) % nb_heaps]) >= heaps[(heap + i) % nb_heaps]; i++);
    heap = (heap + i) % nb_heaps;
    nb_elements = heaps[heap] - (xor ^ heaps[heap]);
    heaps[heap] ^= xor;

    if (misere && heaps_max (heaps, nb_heaps) <= 1)
    {
      heaps[heap] ^= xor;
      if (heaps_non_empty (heaps, nb_heaps) % 2 == 0 || heaps_max (heaps, nb_heaps) <= 1)
        nb_elements = heaps[heap];
      else
        nb_elements = heaps[heap] - 1;
    }
    else
      heaps[heap] ^= xor;
  }

  struct move ret = { heap + 1, nb_elements };
  return ret;
}

static struct move
i_play (int *heaps, int nb_heaps)
{
  printf ("Humm, i'm thinking...\n");
  sleep ((rand () % 3 + 1) * (heaps_non_empty (heaps, nb_heaps) - 1));
  printf ("OK, let me play.\n");
  sleep (1);
  return heaps_best_move (heaps, nb_heaps);
}

static struct move
you_play (int *heaps, int nb_heaps)
{
  char buffer[512];
  char *last = 0;

  int heap;
  do
  {
    printf ("Choose a heap to remove elements from: ");
    fgets (buffer, sizeof (buffer) / sizeof (*buffer), stdin);
    heap = strtol (buffer, &last, 10);
  }
  while (*buffer == 0 || *last != '\n' || heap < 1 || heap > nb_heaps || !heaps[heap - 1]);
  heap--;

  int nb_elements = heaps[heap];
  if (nb_elements > 1)
    do
    {
      printf ("Choose the number of elements to remove from heap %i (out of %i): ", heap + 1, heaps[heap]);
      fgets (buffer, sizeof (buffer) / sizeof (*buffer), stdin);
      nb_elements = strtol (buffer, &last, 10);
    }
    while (*buffer == 0 || *last != '\n' || nb_elements < 1 || nb_elements > heaps[heap]);

  struct move ret = { heap + 1, nb_elements };
  return ret;
}

static int
heaps_display (int *heaps, int nb_heaps)
{
  int nb_elements = 0;
  if (!heaps_non_empty (heaps, nb_heaps))
    printf ("No more heaps.");
  else
    for (int i = 0; i < nb_heaps; i++)
    {
      if (!heaps[i])
        continue;
      printf ("Heap %5i:", i + 1);
      for (int j = 0; j < 2 * (heaps_max (heaps, nb_heaps) - heaps[i]) / 2; j++)
        printf (" ");
      for (int j = 0; j < heaps[i]; j++)
        printf (" |");
      for (int j = 0; j < 2 * (heaps_max (heaps, nb_heaps) - heaps[i]) / 2; j++)
        printf (" ");
      printf (" [%i element(s)]\n", heaps[i]);
      nb_elements += heaps[i];
   }
  printf ("\n");

  return nb_elements;
}

int
main (int argc, char **argv)
{
  // Initialization.
  srand (time (0));
  int *heaps = 0;
  int nb_heaps = 0;
  for (int i = 1; i < argc; i++)
  {
    char *last;
    int heap = strtol (argv[i], &last, 10);
    if (*argv[i] == 0 || *last != 0)
      printf ("NOK %s\n", argv[i]);
    else
    {
      nb_heaps++;
      heaps = realloc (heaps, nb_heaps * sizeof (*heaps));
      heaps[nb_heaps - 1] = heap;
    }
  }

  if (!nb_heaps || !heaps_non_empty (heaps, nb_heaps))
  {
    nb_heaps = 4;
    heaps = realloc (heaps, nb_heaps * sizeof (*heaps));
    for (int i = 0; i < nb_heaps; i++)
      heaps[i] = 1 + 2 * i;
  }

  int nb_elements = 0;
  for (int i = 0; i < nb_heaps; i++)
    nb_elements += heaps[i];

  printf ("%1$i elements are gathered into %2$i heaps:\n", nb_elements, nb_heaps);
  heaps_display (heaps, nb_heaps);

  // Playing
  printf ("Each player (you and I) alternate taking any number of elements from any single one of the %i heaps.\n", nb_heaps);
  printf ("The %s is the one taking the last element.\n", misere ? "loser" : "winner");

  char buffer[512];
  char player = 'H';
  printf ("Do you want to play first ([y]es/no) ? ");
  if (fgets (buffer, sizeof (buffer) / sizeof (*buffer), stdin) && !strncmp ("n", buffer, 1))
    player = 'C';

  while (heaps_non_empty (heaps, nb_heaps))
  {
    //heaps_display (heaps, nb_heaps);
    struct move m;
    switch (player)
    {
      case 'H':
        printf ("> Your turn.\n");
        m = you_play (heaps, nb_heaps);
        player = 'C';
        break;
      case 'C':
        printf ("> My turn.\n");
        m = i_play (heaps, nb_heaps);
        player = 'H';
        break;
    }

    printf ("Removing %1$i element(s) from heap %2$i:\n\n", m.nb, m.heap);
    heaps[m.heap - 1] -= m.nb;

    heaps_display (heaps, nb_heaps);
  }

  if (misere && player == 'H')
    printf ("I loose.\n");
  else
    printf ("You loose (Je peux perdre, mais je gagne toujours).\n");

  free (heaps);
}
