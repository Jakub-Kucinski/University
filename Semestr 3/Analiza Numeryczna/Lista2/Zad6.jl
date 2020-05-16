# using Printf

# s = Float64(1.0);
# c = Float64(0.0);
# k = 2;
# @printf("%d     %lf \n", k, 2^(k-1) * s);

# while k < 128
#     s = sqrt(Float64(0.5) * (Float64(1.0) - c) );
#     c = sqrt(Float64(0.5) * (Float64(1.0) + c) );
#     @printf("%d     %lf \n", k, 2^(k-1) * s);
#     k += 1;
# end


using Printf
using Core

function zad()
    s = BigFloat(1, 128);
    c = BigFloat(0, 128);
    k = 2;
    @printf("%d     %lf \n", k, 2^(k-1) * s);
    k = 3;
    while k < 128
        c = sqrt(BigFloat(1/2, 128) * (BigFloat(1, 128) + c) );
        s = s / (2*c);
        @printf("%d     %lf \n", k, 2^(k-1) * s);
        k += 1;
    end
end

zad()