{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
, gcc ? pkgs.gcc
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./../..;

  phases = [ "unpackPhase" "patchPhase" "checkPhase" "configurePhase" "installPhase" ];
  checkPhase = ''
    make gcctest
  '';

  patches = [ ./0001-ln-to-cp.patch ./0002-hardeningDisable-for-gcc-wrap.patch ];

  postInstall = ''
    ln -s $out/bin/gcc-wrap $out/bin/cc
    substituteInPlace $out/bin/gcc-wrap --replace 'exec gcc' 'exec ${gcc}/bin/gcc'
  '';

  doCheck = true;
  dontDisableStatic = true;

  hardeningDisable = ["all"];
  nativeBuildInputs = [ gcc ];

  buildInputs = [ gnumake ];
}
