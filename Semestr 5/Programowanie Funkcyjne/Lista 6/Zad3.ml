let foo = 
    let cnt = ref 0 in
        let next () = 
            let r = !cnt 
            in cnt := r + 1; r
        and reset () = cnt := 0
        in (next, reset);;
    
let (next, reset) = foo;;

next();;
next();;
next();;
next();;
reset();;
next();;
next();;
next();;