function Fibrec(n)
{
    if (n == 1 || n == 2)
        return 1;
    return Fibrec(n - 1) + Fibrec(n - 2);
}

function Fibiter(n)
{
    if (n == 1 || n == 2)
        return 1;
    var fiba;
    var fibb = 1;
    var fibc = 1;
    var i = 3;
    while (i <= n)
    {
        fiba = fibb;
        fibb = fibc;
        fibc = fiba + fibb;
        i += 1;
    }
    return fibc;
}

for (var i = 10; i < 35; i = i + 1)
{
    console.log("n="+i.toString());
    console.time("Time rec");
    Fibrec(i);
    console.timeEnd("Time rec");
    console.time("Time iter");
    Fibiter(i);
    console.timeEnd("Time iter");
}