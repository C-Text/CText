# This shell defines a development environment for the CText project.
let
  pkgs = import <nixpkgs> {};
in pkgs.mkShell rec {
   buildInputs = with pkgs; [
    gcc
    gnumake
    pkg-config

    SDL.dev
    SDL_image
    SDL_gfx
    gtk3

    # debugging tools
    gdb
    valgrind
   ];
}