The library implements what is known as Shamir's method for secret sharing in the Galois Field 2**8. In slightly simpler words, this is N-of-M secret-sharing byte-by-byte. Essentially this allows us to split  a secret S into any M shares S(1) to S(M) such that any N of those shares can be used to reconstruct S but any less than N shares yields no information whatsoever.


- [Reference](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing)

- [Reference](https://manpages.ubuntu.com/manpages/xenial/man7/gfshare.7.html)