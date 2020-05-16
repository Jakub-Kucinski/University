function podpunkt1(){
    var obj = {
        x : 6.34,
        123 : 43,
        variable : 9
    }

    console.log(obj.x)
    console.log(obj['x'])

    console.log(obj.x instanceof Number)
    console.log(obj['x'] instanceof Number)

    obj.x = 5.1
    console.log(obj.x)

    obj['x'] = 5.2
    console.log(obj.x)

    console.log(obj['y'])
    console.log(obj.y)

    console.log(obj['123'])
    // console.log(obj.123) // wywołuje błąd!

    const variable = 'x'
    // poniższe dwie linijki dają różne wyniki!
    console.log(obj[variable])
    console.log(obj.variable)
}

function podpunkt2(){
    var obj = {
        x : 6.34,
        123 : 43,
        variable : 9
    }

    var obj1 = {
        x : 6.35,
        123 : 45,
        variable : 10
    }

    var obj2 = {
        x : 6.35,
        123 : 45,
        variable : 10
    }
    //console.log(Object.keys(obj))
    console.log(obj[1]) // undefined
    obj[1]='a'
    console.log(obj[1]) // 'a'
    obj[obj2] = 2
    console.log(obj[obj2]) // 2
    console.log(obj[obj1]) // 2
    console.log(Object.keys(obj))
}

function podpunkt3(){
    var tab = [0,1,2,3,4,5,6,7,8,9]
    var obj = {
        x : 6.34,
        123 : 43,
        variable : 9
    }

    console.log(tab['cokolwiek']) // undefined
    console.log(tab['c']) // undefined
    console.log(tab['5']) // 5
    console.log(tab[obj]) // undefined
    console.log(tab.length) //10
    tab['ags3g'] = 40;
    console.log(tab)
    console.log(tab['ags3g'])
    console.log(tab.length) //10
    tab[10] = 10
    console.log(tab)
    console.log(tab.length) //11
    tab.length = 15
    console.log(tab)
    console.log(tab.length) //15
    tab.length = 5 //
    console.log(tab)
    console.log(tab.length) //5
    console.log(tab[5]) // undefined
}

// podpunkt1()
podpunkt2()
// podpunkt3()