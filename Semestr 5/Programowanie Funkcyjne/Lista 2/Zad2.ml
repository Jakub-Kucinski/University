let rec len xs = 
    match xs with
    y::ys -> 1 + len ys
    | [] -> 0;;

let cycle xs k = 
    let n = len xs in
        let rec loop ys i = 
            if i = n - k 
            then []
            else (List.hd ys) :: (loop (List.tl ys) (i + 1)) in
                let rec loop2 ys j = 
                    if j <= n - k
                    then loop2 (List.tl ys) (j+1)
                    else ys in 
                        let rec loop3 zs j acc = 
                            if j = k
                            then acc
                            else (List.hd zs) :: (loop3 (List.tl zs) (j+1) acc)
                            in loop3 (loop2 xs 1) 0 (loop xs 0);;
