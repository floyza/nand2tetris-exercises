{ pkgs ? import <nixpkgs> {} }:
# let
#   nixpkgs = builtins.fetchGit {
#     url = https://github.com/NixOS/nixpkgs;
#     ref = "refs/heads/master";
#     rev = "4849a58f68b13f3fd800d9e0c8806805382bf801";
#   };
# in
# with (import nixpkgs {});
with pkgs;
mkShell {
  buildInputs = [
    gcc
    ccls
  ];
}
