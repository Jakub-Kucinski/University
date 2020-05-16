class Fixnum
    def czynniki
        t = []
        i = 1
        while i <= self
            if self % i == 0
                t.append(i)
            end
            i = i + 1
        end
        return t
    end
    def ack(y)
        if self == 0
            return y + 1
        elsif y == 0
            n = self - 1
            return n.ack(1)
        else
            n = self - 1
            return n.ack(self.ack(y-1))
        end
    end
    def doskonala
        sum = 0
        self.czynniki.each{|val| sum += val}
        sum -= self
        if self == sum
            return true
        else
            return false
        end
    end
    def slownie
        n = self % 10
        slowo = case n
            when 9
                "dziewięć"
            when 8
                "osiem"
            when 7
                "siedem"
            when 6
                "sześć"
            when 5
                "pięć"
            when 4
                "cztery"
            when 3
                "trzy"
            when 2
                "dwa"
            when 1
                "jeden"
            else "zero"
        end
        if self < 10
            return slowo
        else
            p = self / 10
            return p.slownie + " " + slowo
        end
    end
end

puts 6.czynniki
puts 2.ack(1)
puts 6.doskonala
puts 61428.slownie