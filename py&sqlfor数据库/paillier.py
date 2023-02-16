import math

import random

def ipow(a, b, n):
    A = a = a % n
    yield A
    t = 1
    while t <= b:
        t <<= 1

    # t = 2**k, and t > b
    t >>= 2
    
    while t:
        A = (A * A) % n
        if t & b:
            A = (A * a) % n
        yield A
        t >>= 1

def rabin_miller_witness(test, possible): 
    return 1 not in ipow(test, possible-1, possible)

smallprimes = (2,3,5,7,11,13,17,19,23,29,31,37,41,43,
               47,53,59,61,67,71,73,79,83,89,97)

def default_k(bits):
    return max(40, 2 * bits)

def is_probably_prime(possible, k=None):
    if possible == 1:
        return True
    if k is None:
        k = default_k(possible.bit_length())
    for i in smallprimes:
        if possible == i:
            return True
        if possible % i == 0:
            return False
    for i in range(int(k)):
        test = random.randrange(2, possible - 1) | 1
        if rabin_miller_witness(test, possible):
            return False
    return True

def generate_prime(bits, k=None):  
    assert bits >= 8

    if k is None:
        k = default_k(bits)

    while True:
        possible = random.randrange(2 ** (bits-1) + 1, 2 ** bits) | 1
        if is_probably_prime(possible, k):
            return possible



def invmod(a, p, maxiter=1000000):
    if a == 0:
        raise ValueError('0 has no inverse mod %d' % p)
    r = a
    d = 1
    for i in range(min(p, maxiter)):
        d = ((p // r + 1) * d) % p
        r = (d * a) % p
        if r == 1:
            break
    else:
        raise ValueError('%d has no inverse mod %d' % (a, p))
    return d

def modpow(base, exponent, modulus):
    result = 1
    while exponent > 0:
        if exponent & 1 == 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
    return result


def get_key(bits):
    p = generate_prime(bits / 2)
    q = generate_prime(bits / 2)
    n = p * q
    return p,q,n


def encrypt(pub, plain):
    n=pub
    n_sq=n*n
    g=n+1
    while True:
        r = generate_prime(round(math.log(n, 2)))
        if r > 0 and r < n:
            break
    x = pow(r, n, n_sq)
    cipher = (pow(g, plain, n_sq) * x) % n_sq
    return cipher







def decrypt(pub, cipher):
    p,q,n=get_key(128)
    priv_l=(p-1)*(q-1)
    priv_m=invmod(priv_l,n)
    x = pow(cipher, priv_l, pub.n_sq) - 1
    plain = ((x // pub.n) * priv_m) % pub.n
    return plain

