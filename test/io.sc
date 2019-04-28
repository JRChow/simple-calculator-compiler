a = 1;
b = 'b';
c = "This is C babe! ";

// Testing `put`
// 11
puti_(a);  // 1
puti(a);  // 1
// bb
putc_(b);  // 'b'
putc(b);  // 'b'
// This is C babe! This is C babe!
puts_(c);  // "This is C babe!"
puts(c); // "This is C babe!"
// 7FUCK!
puti_(1 + 2 * 3);
putc_('F');
puts("UCK!");

