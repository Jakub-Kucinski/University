class Funkcja
    def initialize(block)
        @block = block
    end
    def value(x)
        @block.call(x)
    end
    def pole(a, b)
        number = 10000.0
        length = (b - a) / number
        sum = 0
        point = a
        while point < b
            sum += self.value(point) * length
            point += length
        end
        sum
    end
    def zerowe(a, b, e)
        number = 1000.0
        length = (b - a) / number
        point = a
        t = []
        while point < b 
            temp = self.value(point)
            if temp == 0.0
                t.append(point)
            end
            newpoint = point + length
            temp2 = self.value(newpoint)
            if (temp < 0.0 and temp2 > 0.0) or (temp > 0.0 and temp2 < 0.0)
                t.append(self.seek(point, newpoint, e))
            end
            point = newpoint
        end
        t 
    end
    def pochodna(x)
        h = 0.00001
        (self.value(x + h) - self.value(x - h)) / (2 * h)
    end
    def seek(a, b, e)
        if self.value(a) > 0.0
            b, a = a, b
        end 
        while self.value(a) - self.value(b) > e 
            temp = (a + b) / 2
            if self.value(temp) > 0.0
                b = temp
            else
                a = temp
            end
        end
        (a+b)/2
    end    
end




class Funkcja2
    def initialize(block)
        @block = block
    end
    def value(x, y)
        @block.call(x, y)
    end
    def objetosc(a, b, c, d)
        number = 1000.0
        length = (b - a) / number
        height = (d - c) / number
        sum = 0
        point1 = a
        while point1 < b
            point2 = c
            while point2 < d
                sum += self.value(point1, point2) * length * height
                point2 += height
            end
            point1 += length
        end
        sum
    end
    def poziomica(a, b, c, d, wysokosc)
        e = 0.0001
        number = 1000.0
        height = (d - c) / number
        layer = c
        t = []
        p = []
        i = 0
        while layer < d
            p.append(layer)
            function = Funkcja.new(lambda {|x| self.value(x, layer) - wysokosc})
            result = function.zerowe(a, b, e)
            if result
                t[i] = result
            end
            layer += height
            i += 1
        end
        return t, p
    end
end

cube = lambda {|x| x*x*x}
przyklad = Funkcja.new(cube)
puts przyklad.value(3)
puts przyklad.pochodna(1)
puts przyklad.pole(0, 3)
przyklad2 = Funkcja.new(lambda {|x| (x-1)*x*(x-2)})
puts przyklad2.zerowe(-5.0, 5.0, 0.000001)
f2 = Funkcja2.new(lambda {|x, y| x + y})
puts f2.value(3, 5)
puts f2.objetosc(0, 5, 0, 5)
t, p = f2.poziomica(0, 5, 0, 5, 2)
i = 0
while t[i]
    t[i].each{|val| print val, "  ", p[i], "\n"}
    i += 1
end