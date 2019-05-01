func max(x, y) {
    if (x > y) {
        return x;
    }
    return y;
}
Main:
puts("Enter 2 numbers: ");
geti(x);
geti(y);
z = max(x, y);
puti_(z);
puts(" is larger");
