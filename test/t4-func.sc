func abs(x) {
    if (x < 0) {
        x = -x;
    }
    return x;
}
main:
puts("Enter an int: ");
geti(y);
puti(abs(y));
