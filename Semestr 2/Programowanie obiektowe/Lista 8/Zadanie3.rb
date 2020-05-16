class Jawna
    def initialize(napis)
        @napis = napis
    end
    def to_s
        return @napis
    end
    def zaszyfruj(klucz)
        nowy = ""
        i = 0
        while @napis[i] 
            nowy = nowy + klucz[@napis[i]]
            i = i + 1
        end
        return Zaszyfrowane.new(nowy)
    end
end

class Zaszyfrowane
    def initialize(napis)
        @napis = napis
    end
    def to_s
        return @napis
    end
    def odszyfruj(klucz)
        nowy = ""
        i = 0
        while @napis[i] 
            nowy = nowy + klucz.key(@napis[i])
            i = i + 1
        end
        return Zaszyfrowane.new(nowy)
    end
end

obiekt = Jawna.new('ruby')
puts obiekt.to_s
t = { 'a' => 'b',
'b' => 'r',
'r' => 'y',
'y' => 'u',
'u' => 'a'
}
obiekt2 = obiekt.zaszyfruj(t)
puts obiekt2.to_s

obiekt3 = obiekt2.odszyfruj(t)
puts obiekt3.to_s

