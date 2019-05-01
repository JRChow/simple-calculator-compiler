func reverseInput() {
    getc(x);
    // Not newline
    if (x != 10) {
        reverseInput();
        putc_(x);
    }
    return 0;
}
Main:
puts("Please enter a line:");
reverseInput();
