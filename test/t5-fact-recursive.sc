func fact(x) {
    if (x == 0)
        return 1;
    return x * fact(x-1);
}

Main:
puts("Enter a number:");
geti(n);
puti(fact(n));
