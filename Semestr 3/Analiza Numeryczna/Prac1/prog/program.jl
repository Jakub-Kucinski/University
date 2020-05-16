using Plots

wolfram = zeros(Float64, 20)
wolfram[1] = 1.0
wolfram[2] = 0.71828182845904523536028747135266249775724709369995957496696762772
wolfram[3] = 0.56343634308190952927942505729467500448550581260008085006606474455
wolfram[4] = 0.46453645613140711824258724217396247981522384329963617470270864952
wolfram[5] = 0.39559954780200964414735126048285009868112787720177870145342438014
wolfram[6] = 0.34468454164698737047617990845556190567047983048928736624642134688
wolfram[7] = 0.30549003693013364202702811216372915806388828027494801124201819956
wolfram[8] = 0.27436153301797609914406257404282923324614085150037548503082203123
wolfram[9] = 0.24902803129726034306372430496719939854197943019658020968956934667
wolfram[10] = 0.22800151548644180472304442168066851233745279173415747807127416106
wolfram[11] = 0.21026515810818538340679883286530886204526638462422731618295185604
wolfram[12] = 0.19509993116082063447870147696895615321405047820923178077154535529
wolfram[13] = 0.18198272336837698713716827075623250597459087697994642493687800896
wolfram[14] = 0.17052370130176741543993168076540741411297481598070962585067550229
wolfram[15] = 0.16042630893253400376131225987155128606262485398931518720683509340
wolfram[16] = 0.15146088553850117517929131340784192075524942987091657965760613327
wolfram[17] = 0.14344677430452525731233514341934984491800678589437772078766336214
wolfram[18] = 0.13623989097759060373825488980436528923312494760116060078902710924
wolfram[19] = 0.12972389988482376433344456506972200232787308927790815997545255215
wolfram[20] = 0.12380383076256994869139616995822245119978530814179637545791658466

function nast()
    nastepny = zeros(Float64, 20)
    e = Base.MathConstants.e
    nastepny[1] = e - (e - 1)
    i = 2
    while i <= 20
        nastepny[i] = e - i * nastepny[i-1]
        i += 1
    end

    i = 1
    while i <= 20
        println(i," & ", nastepny[i]," & ", wolfram[i])
        i += 1
    end

    blad_wzgl = zeros(Float64, 20)
    i = 1
    while i <= 20
        blad_wzgl[i] = abs(wolfram[i] - nastepny[i])/wolfram[i]
        i += 1
    end
    dokladne_cyfry = zeros(Float64, 20)
    i = 1
    while i <=20
        dokladne_cyfry[i] = - log10(blad_wzgl[i])
        i += 1
    end
    x = 1:20
    pl = plot(x, dokladne_cyfry, size=(600, 400), xticks=0:2:20, yticks=-3:2:18, shape=:circle, ms=4, lw=3, 
    title="Liczba dokladnych cyfr watosci obliczonej rekurencyjnie ",label=["Liczba dokladnych cyfr"])
    savefig(pl, "plot.png");
end

function poprz()
    poprzedni = zeros(Float64, 20)
    e = Base.MathConstants.e
    poprzedni21 = e / (21.0 + 1.0)
    poprzedni[20] = (e - poprzedni21) / 21.0
    i = 19
    while i >=1
        poprzedni[i] = (e - poprzedni[i+1]) / (i+1)
        i -= 1
    end

    i = 1
    while i <= 20
        println(i," & ", poprzedni[i]," & ", wolfram[i])
        i += 1
    end

    blad_wzgl2 = zeros(Float64, 20)
    i = 1
    while i <= 20
        blad_wzgl2[i] = abs(wolfram[i] - poprzedni[i])/wolfram[i]
        i += 1
    end
    dokladne_cyfry2 = zeros(Float64, 20)
    i = 1
    while i <=20
        dokladne_cyfry2[i] = - log10(blad_wzgl2[i])
        i += 1
    end
    x = 1:20
    pl = plot(x, dokladne_cyfry2, size=(800, 600), xticks=0:2:20, yticks=-3:2:18, shape=:circle, ms=4, lw=3,
        title="Liczba dokladnych cyfr w systemie dziesietnym dla przyblizenia y(21) = e/22",label=["Liczba dokladnych cyfr"])
    savefig(pl, "plot2.png");
end

function poprzlepszy()
    poprzednilepszy = zeros(Float64, 40)
    e = Base.MathConstants.e
    poprzednilepszy41 = e / (42.0)
    poprzednilepszy[40] = (e - poprzednilepszy41) / 41.0
    i = 39
    while i >=1
        poprzednilepszy[i] = (e - poprzednilepszy[i+1]) / (i+1)
        i -= 1
    end

    i = 1
    while i <= 20
        println(i," & ", poprzednilepszy[i]," & ", wolfram[i])
        i += 1
    end

    blad_wzgl3 = zeros(Float64, 20)
    i = 1
    while i <= 20
        blad_wzgl3[i] = abs(wolfram[i] - poprzednilepszy[i])/wolfram[i]
        i += 1
    end
    dokladne_cyfry3 = zeros(Float64, 20)
    i = 1
    while i <=20
        dokladne_cyfry3[i] = - log10(blad_wzgl3[i])
        i += 1
    end
    x = 1:20
    pl = plot(x, dokladne_cyfry3, seriestype=:path, size=(800, 600), xticks=0:2:20, ylims=(-3, 18), yticks=-3:2:18, 
    shape=:circle, ms=4, lw=3, title="Liczba dokladnych cyfr w systemie dziesietnym dla przyblizenia y(41) = e/42",label=["Liczba dokladnych cyfr"],
    legend=:bottomright)
    savefig(pl, "plot3.png");
end

nast()
poprz()
poprzlepszy()