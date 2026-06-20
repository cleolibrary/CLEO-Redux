CLEO Redux supports `re3` or `reVC` (both 32-bit and 64-bit).

During installation you must select the correct version of `re3` or `reVC`: either 32-bit or 64-bit.

When running on `re3` and `reVC` make sure the game directory contains the file `re3.pdb` (for **re3**) or `reVC.pdb` (for **reVC**). Due to the dynamic nature of memory addresses in those implementations CLEO Redux relies on debug information stored in the PDB file to correctly locate itself.

> CLEO Redux also supports `reLCS` and `reVCS` should they ever be released. The requirements are the same.
>
> It also works with GTA SA Reversed (`gta_reversed.dll` & `gta_reversed.pdb`).

ASI Loader is required unless the game has built-in support for ASI plugins (e.g. via the MSS library).
