//主にn = 1e9の時に用いる
//フェルマーの小定理より、pが素数の時
//a^(p - 1) = 1(mod p)より、
//a^(-1)(mod p) = a^(p - 2)
//つまりa^(1e9 + 7 - 2)をかければ良い
//繰返し二乗法を用いればすぐにできる。詳しくは156d.cpp