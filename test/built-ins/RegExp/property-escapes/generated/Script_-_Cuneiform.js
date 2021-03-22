// Copyright 2020 Mathias Bynens. All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/*---
author: Mathias Bynens
description: >
  Unicode property escapes for `Script=Cuneiform`
info: |
  Generated by https://github.com/mathiasbynens/unicode-property-escapes-tests
  Unicode v13.0.0
esid: sec-static-semantics-unicodematchproperty-p
features: [regexp-unicode-property-escapes]
includes: [regExpUtils.js]
---*/

const matchSymbols = buildString({
  loneCodePoints: [],
  ranges: [
    [0x012000, 0x012399],
    [0x012400, 0x01246E],
    [0x012470, 0x012474],
    [0x012480, 0x012543]
  ]
});
testPropertyEscapes(
  /^\p{Script=Cuneiform}+$/u,
  matchSymbols,
  "\\p{Script=Cuneiform}"
);
testPropertyEscapes(
  /^\p{Script=Xsux}+$/u,
  matchSymbols,
  "\\p{Script=Xsux}"
);
testPropertyEscapes(
  /^\p{sc=Cuneiform}+$/u,
  matchSymbols,
  "\\p{sc=Cuneiform}"
);
testPropertyEscapes(
  /^\p{sc=Xsux}+$/u,
  matchSymbols,
  "\\p{sc=Xsux}"
);

const nonMatchSymbols = buildString({
  loneCodePoints: [
    0x01246F
  ],
  ranges: [
    [0x00DC00, 0x00DFFF],
    [0x000000, 0x00DBFF],
    [0x00E000, 0x011FFF],
    [0x01239A, 0x0123FF],
    [0x012475, 0x01247F],
    [0x012544, 0x10FFFF]
  ]
});
testPropertyEscapes(
  /^\P{Script=Cuneiform}+$/u,
  nonMatchSymbols,
  "\\P{Script=Cuneiform}"
);
testPropertyEscapes(
  /^\P{Script=Xsux}+$/u,
  nonMatchSymbols,
  "\\P{Script=Xsux}"
);
testPropertyEscapes(
  /^\P{sc=Cuneiform}+$/u,
  nonMatchSymbols,
  "\\P{sc=Cuneiform}"
);
testPropertyEscapes(
  /^\P{sc=Xsux}+$/u,
  nonMatchSymbols,
  "\\P{sc=Xsux}"
);
