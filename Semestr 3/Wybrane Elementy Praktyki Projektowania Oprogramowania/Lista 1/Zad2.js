function zbior()
{
    var tablica = [];
    for (var i = 1; i < 100000; i++)
    {
        let k = i;
        let sum = 0;
        let czy = true;
        while (k > 0)
        {
            sum += k % 10;
            if (k % (k % 10) != 0)
            {
                czy = false;
                break;
            }
            k = (k - (k % 10)) / 10;
        }
        if (czy == true && i % sum == 0)
            tablica.push(i);
    }
    return tablica;
}
console.log(zbior());