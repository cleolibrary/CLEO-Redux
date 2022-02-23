CLEO Redux only supports "Windows D3D9 MSS 32bit" version of `re3` or `reVC`.

- Copy `cleo_redux.asi` to the game directory (with the main executable file).

- Run the game

When running on `re3` and `reVC` make sure the game directory contains the file `re3.pdb` (for **re3**) or `reVC.pdb` (for **reVC**). Due to the dynamic nature of memory addresses in those implementations CLEO Redux relies on debug information stored in the PDB file to correctly locate itself.
