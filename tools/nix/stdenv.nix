{ stdenv
, callPackage
}:

stdenv.override {
  cc = callPackage ./. {};
}
