def run
    yield
end

# run { print "dwa dodac dwa jest ", 2 + 2 }

def dodawanie
    yield 2,2
    yield 3,4
end
    
dodawanie {|x, y| puts x + y }

def foo(x, y, &blok)
    yield x, y
end


foo(2, 3) {|a, b| puts a + b }

def test
    return 1, 2
end

a, b = test()
puts a, b