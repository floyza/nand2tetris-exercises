{ pkgs ? import <nixpkgs> {} }:
with pkgs;
mkShell {
  buildInputs = [
    gcc
    ccls
    cmake
  ];
}
