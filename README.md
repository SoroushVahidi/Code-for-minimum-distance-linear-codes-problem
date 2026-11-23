# Minimum Distance of Binary Linear Codes: Genetic Algorithm (C++) and Exact Model (MiniZinc)

> Course project (Artificial Intelligence, about 2021–2022), kept for reference.

**What this is.** The **minimum distance** of a binary linear code is the smallest Hamming weight of a nonzero codeword. It decides how many errors the code can detect or correct, and computing it is NP-hard. The input here is a set of parity checks: each row lists the variable positions whose XOR must be 0. Two tools work on it:

- `exact.mzn` is an exact **MiniZinc** model. It finds a nonzero 0/1 vector that satisfies every parity row (each row sum is even) with the fewest ones.
- `inexact.cpp` is a **genetic algorithm** in C++ for larger instances. It evolves 0/1 vectors with elitism, mutation, and restarts, and its fitness rewards satisfied parity rows and low weight.

## Report

- S. Vahidi. *Minimum distance of linear codes.* Unpublished project report, 2022. DOI: [10.13140/RG.2.2.32533.81128](https://doi.org/10.13140/RG.2.2.32533.81128)
- The same report is included as `AI_3891_PROJECT.pdf`.

```bibtex
@misc{vahidi2022mindist,
  author = {Vahidi, Soroush},
  title  = {Minimum distance of linear codes},
  year   = {2022},
  note   = {Unpublished project report},
  doi    = {10.13140/RG.2.2.32533.81128}
}
```

## Files

| File | What it is |
|---|---|
| `exact.mzn` | Exact MiniZinc model (`solve minimize count`). It includes a data file `large3.dzn` with `row`, `col`, `maxi` and `arr` |
| `inexact.cpp` | Genetic algorithm. Reads `large2.txt` and writes `large2f_answer.txt`. GA parameters (`tahlil`, `rst`, `prm`, `nokhbe` = elite size) are globals at the top |
| `small_instances_for_exact_code.rar` | Small instances (`.dzn`) for the MiniZinc model |
| `large_instances_for_inexact_code.rar` | Larger instances for the GA |
| `AI_3891_PROJECT.pdf` | Project report |

## Run

```bash
# Exact model (needs MiniZinc and a MIP/CP solver)
minizinc exact.mzn            # edit the include line to choose the .dzn instance

# Genetic algorithm
g++ -O2 -o ga inexact.cpp
./ga                          # reads large2.txt in the working directory
```

Extract the matching `.rar` archive first. Input and output file names are set inside the sources.

## License

MIT, see `LICENSE`.
