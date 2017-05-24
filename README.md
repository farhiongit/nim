# nim
Play [Nim](https://en.wikipedia.org/wiki/Nim) (and loose) against computer ("Je peux perdre, mais je gagne toujours").

This toy program aims at implementing the ever winning algorithm described at https://en.wikipedia.org/wiki/Nim#Mathematical_theory.

Here is a sample of an interactive game between the human player ("you") and the computer ("I").
```
16 elements are gathered into 4 heaps:
Heap     1:       |       [1 element(s)]
Heap     2:     | | |     [3 element(s)]
Heap     3:   | | | | |   [5 element(s)]
Heap     4: | | | | | | | [7 element(s)]

Each player (you and I) alternate taking any number of elements from any single one of the 4 heaps.
The loser is the one taking the last element.
Do you want to play first ([y]es/no) ? *y*
> Your turn.
Choose a heap to remove elements from: *1*
Removing 1 element(s) from heap 1:

Heap     2:     | | |     [3 element(s)]
Heap     3:   | | | | |   [5 element(s)]
Heap     4: | | | | | | | [7 element(s)]

> My turn.
Humm, i'm thinking...
OK, let me play.
Removing 1 element(s) from heap 4:

Heap     2:    | | |    [3 element(s)]
Heap     3:  | | | | |  [5 element(s)]
Heap     4: | | | | | | [6 element(s)]

> Your turn.
Choose a heap to remove elements from: *4*
Choose the number of elements to remove from heap 4 (out of 6): *2*
Removing 2 element(s) from heap 4:

Heap     2:   | | |   [3 element(s)]
Heap     3: | | | | | [5 element(s)]
Heap     4:  | | | |  [4 element(s)]

> My turn.
Humm, i'm thinking...
OK, let me play.
Removing 2 element(s) from heap 2:

Heap     2:     |     [1 element(s)]
Heap     3: | | | | | [5 element(s)]
Heap     4:  | | | |  [4 element(s)]

> Your turn.
Choose a heap to remove elements from: *2*
Removing 1 element(s) from heap 2:

Heap     3: | | | | | [5 element(s)]
Heap     4:  | | | |  [4 element(s)]

> My turn.
Humm, i'm thinking...
OK, let me play.
Removing 1 element(s) from heap 3:

Heap     3: | | | | [4 element(s)]
Heap     4: | | | | [4 element(s)]

> Your turn.
Choose a heap to remove elements from: *3*
Choose the number of elements to remove from heap 3 (out of 4): *2*
Removing 2 element(s) from heap 3:

Heap     3:   | |   [2 element(s)]
Heap     4: | | | | [4 element(s)]

> My turn.
Humm, i'm thinking...
OK, let me play.
Removing 2 element(s) from heap 4:

Heap     3: | | [2 element(s)]
Heap     4: | | [2 element(s)]

> Your turn.
Choose a heap to remove elements from: *3*
Choose the number of elements to remove from heap 3 (out of 2): *1*
Removing 1 element(s) from heap 3:

Heap     3:  |  [1 element(s)]
Heap     4: | | [2 element(s)]

> My turn.
Humm, i'm thinking...
OK, let me play.
Removing 2 element(s) from heap 4:

Heap     3: | [1 element(s)]

> Your turn.
Choose a heap to remove elements from: *3*
Removing 1 element(s) from heap 3:

No more heaps.
You loose (Je peux perdre, mais je gagne toujours).
```
