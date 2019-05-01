func reverseInput() {
    getc(x);
    // Not newline
    if (x != 10) {
        reverseInput();
        putc(x);
    }
}
Main:
puts("Please enter a line:");
reverseInput();
