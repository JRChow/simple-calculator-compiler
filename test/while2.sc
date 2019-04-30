i = 0;
x = 10;
z = 1;
while (i < 3) {
    x = x - z;
    i = i + z;
}
puti(x);
puts("Should see 7");
puti(z);
puts("Should see 1");
puti(i);
puts("Should see 3");
