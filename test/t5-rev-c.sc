func reverseInput() {
    getc(x);
    // Not newline
    if (x != 10) {
        reverseInput();
        putc_(x);
    }
}
Main:
puts("Please enter a line:");
reverseInput();
