class Wezel
    def initialize(val)
        @value = val
        @last = nil
        @next = nil
    end
    def set_next(obj)
        @next = obj
    end
    def set_last(obj)
        @last = obj
    end
    def set_value(val)
        @value = val
    end
    def get_next
        @next
    end
    def get_last
        @last
    end
    def get_value
        @value
    end
end

class Kolekcja
    def initialize
        @start = nil
        @end = nil
    end
    def add(val)
        if @start == nil
            @start = Wezel.new(val)
            @end = @start
        else 
            temp = Wezel.new(val)
            @end.set_next(temp)
            temp.set_last(@end)
            @end = temp
        end
    end
    def pop
        if @start == nil
            nil
        else
            temp = @end.get_value
            if @start == @end
                @start = nil
                @end = nil
            else
                @end = @end.get_last
                @end.set_next(nil)
            end
            temp
        end
    end
    def length
        temp = @start
        i = 0
        while temp
            i += 1
            temp = temp.get_next
        end
        i
    end
    def get(i)
        if i < 0
            return nil
        end
        temp = @start
        while temp && (i > 0)
            i -= 1
            temp = temp.get_next
        end
        if temp == nil
            nil
        else
            temp.get_value
        end
    end
    def set(i, val)
        if i < 0
            return nil
        end
        temp = @start
        while temp && (i > 0)
            i -= 1
            temp = temp.get_next
        end
        if temp == nil
            nil
        else
            temp.set_value(val)
            i
        end
    end
    def swap(i, j)
        temp1 = self.get(i)
        if temp1 == nil
            return nil
        end
        temp2 = self.get(j)
        if temp2 == nil
            return nil
        end
        self.set(i, temp2)
        self.set(j, temp1)
        1
    end
    def printall
        temp = @start
        while temp
            puts temp.get_value
            temp = temp.get_next
        end
    end
    def get_start
        @start
    end
    def get_end
        @end
    end
end

class Sortowanie
    def initialize
    end
    def sort1(obj)
        size = obj.length
        i = 0
        while i < size
            j = 1
            n = size - i
            while j < n
                temp1 = obj.get(j-1)
                temp2 = obj.get(j)
                if temp1 > temp2
                    obj.swap(j-1, j)
                end
                j += 1
            end
            i += 1
        end
        obj
    end
    def sort2(obj)
        size = obj.length
        i = 0
        while i < size
            point = i
            j = i + 1
            while j < size
                if obj.get(j) < obj.get(point)
                    point = j
                end
                j += 1
            end
            obj.swap(point, i)
            i += 1
        end
        obj
    end
end


kol1 = Kolekcja.new
kol2 = Kolekcja.new
i = 100
while i >= 0
    kol1.add(rand(1000))
    kol2.add(rand(1000))
    i -= 1
end

require 'time' 
sort = Sortowanie.new
t1 = Time.now
sort.sort2(kol1)
t2 = Time.now
sort.sort1(kol2)
t3 = Time.now
puts t2-t1
puts t3-t2





# kol.printall
# sort = Sortowanie.new
# sort.sort1(kol)
# kol.printall


            
