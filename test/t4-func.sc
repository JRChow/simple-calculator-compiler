func abs(x) {
    neg = -1;
    if (x < z) {
        x = mul(x, -1);
    }
    return x;
}

func mul(x, y) {
    return x * y;
}
Main:
x = -789;
z = 0;
puti(abs(x));
puts("should see 789");
puti(x);
puts("should see -789");

