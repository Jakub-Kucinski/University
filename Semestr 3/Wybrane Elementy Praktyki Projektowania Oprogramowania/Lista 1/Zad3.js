function zbior()
{
    var tablica = [];
    for (var i = 2; i < 100000; i++)
    {
        let k = 2;
        let czy = true;
        while (k * k <= i)
        {
            if (i % k == 0)
            {
                czy = false;
                break;
            }
            k += 1;
        }
        if (czy)
            tablica.push(i);
    }
    return tablica;
}
console.log(zbior());