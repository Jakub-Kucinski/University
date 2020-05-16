using QuadGK
using Plots
using Plots.PlotMeasures

function metoda_zlozona_trapezow(f::Function, a::Float64, b::Float64, n::Int64)
    suma = 0.0
    h = (b-a)/Float64(n)
    for i = 1 : n-1
        suma = suma + f(a + i*h)
    end
    wynik = 0.5*h*(f(a) + f(b) + 2*suma)
    return wynik
end


function metoda_zlozona_trapezow_posrednie_do_exp_2_n(f::Function, a::Float64, b::Float64, n::Int64)
    wyniki = zeros(Float64, n+1)
    h = (b-a)
    wyk = 1
    x_i = 0.0
    wyniki[1] = 0.5*h*(f(a) + f(b))
    for k = 1 : n
        suma = 0.0
        h = h/2
        for i = 1 : wyk
            suma = suma + f(a+(2*i-1)*h)
        end
        wyniki[k+1] = 0.5 * wyniki[k] + h * suma
        wyk = wyk*2
    end
    return wyniki
end


function metoda_zlozona_simpsona(f::Function, a::Float64, b::Float64, n::Int64)
    if n % 2 == 1
        n = n + 1
    end
    suma1 = 0.0
    suma2 = 0.0
    h = (b-a)/Float64(n)
    for i = 1 : n/2
        suma1 = suma1 + f(a + (2*i-1)*h)
    end
    for i = 1 : (n/2)-1
        suma2 = suma2 + f(a + 2*i*h)
    end
    wynik = h*(f(a) + f(b) + 4*suma1 + 2*suma2)/3.0
    return wynik
end


function metoda_zlozona_simpsona_posrednie_do_exp_2_n(f::Function, a::Float64, b::Float64, n::Int64)
    wyniki = zeros(Float64, n+1)
    wyk = Int64(1)
    wyniki[1] = (b-a)/6.0 * (f(a) + f(b) + 4* f((b+a)/2.0) )
    for i = 1 : n
        wyk = wyk * 2
        wyniki[i+1] = metoda_zlozona_simpsona(f, a, b, wyk)
    end
    return wyniki
end


function metoda_romberga(f::Function, a::Float64, b::Float64, n::Int64)
    R = metoda_zlozona_trapezow_posrednie_do_exp_2_n(f, a, b, n)
    pot4 = 1.0
    for k = 1 : n
        pot4 = pot4 * 4.0
        for i = n :-1: k
            R[i+1] = (pot4 * R[i+1] - R[i])/(pot4 - 1)
        end
    end
    return R[n+1]
end


function metoda_romberga_posrednie_do_n(f::Function, a::Float64, b::Float64, n::Int64)
    R = metoda_zlozona_trapezow_posrednie_do_exp_2_n(f, a, b, n)
    pot4 = 1.0
    for k = 1 : n
        pot4 = pot4 * 4.0
        for i = n :-1: k
            R[i+1] = (pot4 * R[i+1] - R[i])/(pot4 - 1)
        end
    end
    return R
end


function testowanie(f::Function, a::Float64, b::Float64, n::Int64)
    wyniki_trapezy = metoda_zlozona_trapezow_posrednie_do_exp_2_n(f, a, b, n)
    wyniki_simpsona = metoda_zlozona_simpsona_posrednie_do_exp_2_n(f, a, b, n)
    wyniki_romberga = metoda_romberga_posrednie_do_n(f, a, b, n)
    x = 0:n
    poprawny_wynik = first(quadgk(f, a, b))
    dokladne_cyfry_trapezy = [-log2(abs((wyniki_trapezy[i]-poprawny_wynik)/poprawny_wynik)) for i = 1 : n+1]
    dokladne_cyfry_simpsona = [-log2(abs((wyniki_simpsona[i]-poprawny_wynik)/poprawny_wynik)) for i = 1 : n+1]
    dokladne_cyfry_romberga = [-log2(abs((wyniki_romberga[i]-poprawny_wynik)/poprawny_wynik)) for i = 1 : n+1]
    pl = plot(x, dokladne_cyfry_trapezy, seriestype = :line, xticks=0:1:n, shape=:circle, ms=4, lw=3,
    title="Liczba dokladnych cyfr", label=["Trapezy", "Simpsona", "Romberga"], legend = :topleft)
    plot!(x, dokladne_cyfry_simpsona, seriestype = :line, xticks=0:1:n, shape=:circle, ms=4, lw=3,
    title="Liczba dokladnych cyfr", label=["Trapezy", "Simpsona", "Romberga"], legend = :topleft)
    plot!(x, dokladne_cyfry_romberga, seriestype = :line, xticks=0:1:n, shape=:circle, ms=4, lw=3,
    title="Liczba dokladnych cyfr", label=["Trapezy", "Simpsona", "Romberga"], legend = :topleft)
    return pl
end


function test_wielomiany()
    wiel1 = plot(-2:0.001:10, x -> (7x -1), seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel1, "wiel1.png");
    wiel_blad1 = testowanie(x -> 7x - 1, -2.0, 10.0, Int64(10.0));
    savefig(wiel_blad1, "wiel_blad1.png");

    wiel2 = plot(-5:0.001:10, x -> x^2 - x + 2, seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel2, "wiel2.png");
    wiel_blad2 = testowanie(x -> x^2 - x + 2, -5.0, 10.0, Int64(10.0));
    savefig(wiel_blad2, "wiel_blad2.png");

    wiel3 = plot(-4:0.001:4, x -> 6x^3 + 21x^2 - 138x + 63, seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel3, "wiel3.png");
    wiel_blad3 = testowanie(x -> 6x^3 + 21x^2 - 138x + 63, -4.0, 4.0, Int64(10.0));
    savefig(wiel_blad3, "wiel_blad3.png");

    wiel4 = plot(-6:0.001:6, x -> x^4 - 13x^3 - 36x^2 + 268x + 560, seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel4, "wiel4.png");
    wiel_blad4 = testowanie(x -> x^4 - 13x^3 - 36x^2 + 268x + 560, -6.0, 6.0, Int64(10.0));
    savefig(wiel_blad4, "wiel_blad4.png");

    wiel5 = plot(-1:0.001:1, x ->  3*x^10 - 5*x^7 + 2*x^6 - 8*x^2 - 5, seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel5, "wiel5.png");
    wiel_blad5 = testowanie(x -> 3x^10 - 5*x^7 + 2*x^6 - 8*x^2 - 5, -1.0, 1.0, Int64(10.0));
    savefig(wiel_blad5, "wiel_blad5.png");

    wiel6 = plot(-4:0.001:4, x -> (x+5)*(x+4)*(x+3)*(x+2)*(x+1)*(x-1)*(x-2)*(x-3)*(x-4)*(x-5), seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wiel6, "wiel6.png");
    wiel_blad6 = testowanie(x -> (x+5)*(x+4)*(x+3)*(x+2)*(x+1)*(x-1)*(x-2)*(x-3)*(x-4)*(x-5), -4.0, 4.0, Int64(10.0));
    savefig(wiel_blad6, "wiel_blad6.png");
end


function test_wymierne()
    wym1 = plot(-1:0.001:1, x -> 1.0/(1.0+25.0*x*x), seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wym1, "wym1.png");
    wym_blad1 = testowanie(x -> 1.0/(1.0+25.0*x^2), -1.0, 1.0, Int64(11.0));
    savefig(wym_blad1, "wym_blad1.png");

    wym2 = plot(-2:0.001:2, x -> (x^3 - 6x^2 + 8x - 1)/(1.0+25.0*x^2), seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wym2, "wym2.png");
    wym_blad2 = testowanie(x -> (x^3 - 6x^2 + 8x - 1)/(1.0+25.0*x^2), -2.0, 2.0, Int64(12.0));
    savefig(wym_blad2, "wym_blad2.png");

    wym3 = plot(-2:0.001:2, x -> (x^6 - 6x^5 + 8x - 1)/(2x^3 - 7x^2 + 5x - 4), seriestype = :line, lw=3, size=(800, 600), left_margin = 10mm,
    title=" ", legend = :none);
    savefig(wym3, "wym3.png");
    wym_blad3 = testowanie(x -> (x^6 - 6x^5 + 8x - 1)/(2x^3 - 7x^2 + 5x - 4), -2.0, 2.0, Int64(10.0));
    savefig(wym_blad3, "wym_blad3.png");

    wym4 = plot(-10:0.001:10, x -> (x^6 + 6x^5 + 17x^4 + 28x^3 + 29x^2 + 18x + 6)/(x^6 + 7x^5 + 26x^4 + 58x^3 + 85x^2 + 75x + 36),  size=(800, 600), left_margin = 10mm,
    seriestype = :line, lw=3, title=" ", legend = :none);
    savefig(wym4, "wym4.png");
    wym_blad4 = testowanie(x -> (x^6 + 6x^5 + 17x^4 + 28x^3 + 29x^2 + 18x + 6)/(x^6 + 7x^5 + 26x^4 + 58x^3 + 85x^2 + 75x + 36), 
    -10.0, 10.0, Int64(12.0));
    savefig(wym_blad4, "wym_blad4.png");
end


function test_tryg_wymierne()
    tryg1 = plot(-10:0.001:10, x -> sin(x)^2 + cos(x)^3 *sin(x),  size=(800, 600), left_margin = 10mm,
    seriestype = :line, lw=3, title=" ", legend = :none);
    savefig(tryg1, "tryg1.png");
    tryg_blad1 = testowanie(x -> sin(x)^2 + cos(x)^3 *sin(x), -10.0, 10.0, Int64(10.0));
    savefig(tryg_blad1, "tryg_blad1.png");

    tryg2 = plot(-10:0.001:10, x -> sin(x) + cos(x)^3 *sin(x) - sin(x)^2 * cos(x)^2,  size=(800, 600), left_margin = 10mm,
    seriestype = :line, lw=3, title=" ", legend = :none);
    savefig(tryg2, "tryg2.png");
    tryg_blad2 = testowanie(x -> sin(x) + cos(x)^3 *sin(x) - sin(x)^2 * cos(x)^2, -10.0, 10.0, Int64(10.0));
    savefig(tryg_blad2, "tryg_blad2.png");

    tryg3 = plot(-10:0.001:10, x -> (sin(x) + cos(x)^3 *sin(x) - sin(x)^2 * cos(x)^2)/(sin(x)^2 + cos(x)^3 *sin(x)+1.5),  size=(800, 600), left_margin = 10mm,
    seriestype = :line, lw=3, title=" ", legend = :none);
    savefig(tryg3, "tryg3.png");
    tryg_blad3 = testowanie(x -> (sin(x) + cos(x)^3 *sin(x) - sin(x)^2 * cos(x)^2)/(sin(x)^2 + cos(x)^3 *sin(x) + 1.5), -10.0, 10.0, Int64(12.0));
    savefig(tryg_blad3, "tryg_blad3.png");

    tryg4 = plot(-10:0.001:10, x -> (cos(x) - cos(x)^3 * sin(x)^2 - sin(x)^2)/(sin(x) + cos(x) *sin(x)^4 - 2*sin(x)^2 * cos(x)^2 + 2),  size=(800, 600), left_margin = 10mm,
    seriestype = :line, lw=3, title=" ", legend = :none);
    savefig(tryg4, "tryg4.png");
    tryg_blad4 = testowanie(x -> (cos(x) - cos(x)^3 * sin(x)^2 - sin(x)^2)/(sin(x) + cos(x) *sin(x)^4 - 2*sin(x)^2 * cos(x)^2 + 2), -10.0, 10.0, Int64(12.0));
    savefig(tryg_blad4, "tryg_blad4.png");
end


test_wielomiany();
test_wymierne();
test_tryg_wymierne();
