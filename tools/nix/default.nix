{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./../..;

  phases = [ "unpackPhase" "patchPhase" "checkPhase" "configurePhase" "installPhase" ];
  checkPhase = ''
    make gcctest
    make -B include/bits # Workaround for nix on debian
  '';

  doCheck = true;

  hardeningDisable = ["all"];

  buildInputs = [ gnumake ];
}
