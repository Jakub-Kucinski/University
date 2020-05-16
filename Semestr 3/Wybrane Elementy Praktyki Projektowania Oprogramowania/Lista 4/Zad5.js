process.stdin.setEncoding('utf8');
process.stdout.write("Podaj swoje imię:\n");

process.stdin.on('readable', () => {
    let chunk = process.stdin.read();
    process.stdout.write(`Witaj ${chunk}`);
});