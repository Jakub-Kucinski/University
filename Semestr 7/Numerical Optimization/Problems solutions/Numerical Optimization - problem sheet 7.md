# Numerical Optimization - problem sheet 7
###### tags: `no2021/2022` `ćwiczenia`
## Task 3

![](https://i.imgur.com/39dfEEf.png)
![](https://i.imgur.com/FXVZ3xI.png)
![](https://i.imgur.com/ZCrBzHQ.png)

$U_i(x) = a \langle v, x \rangle v=avv^Tx$
$U_i = a_iz_iz_i^T$

$$p_k = S_{k+1}q_k = S_kq_k+U_kq_k = S_k q_k + a_k z_k z_k^T q_k$$

$$p_k - S_k q_k = a_k z_k z_k^T q_k$$

$$(p_k - S_k q_k)(p_k - S_k q_k)^T = (a_k z_k z_k^T q_k)(a_k z_k z_k^T q_k)^T$$

$$\frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{a_k} = a_k z_k(z_k^Tq_k)^2 z_k^T$$

$$\frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{a_k(z_k^Tq_k)^2} = a_k z_kz_k^T$$

$$S_{k+1} = S_k + a_k z_kz_k^T$$

<!-- $$S_{k+1} = S_k + \frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{a_k(z_k^Tq_k)^2}$$
 -->
$$q_k^TS_{k+1}q_k = q_k^TS_kq_k + q_k^Ta_k z_kz_k^Tq_k$$

$$S_{k+1}q_k = p_k$$

$$q_k^Tp_k = q_k^TS_kq_k + a_k (q_k^Tz_k)^2$$

$$a_k (z_k^Tq_k)^2 = q_k^Tp_k - q_k^TS_kq_k$$

$$S_{k+1} = S_k + U_k$$

$$S_{k+1} = S_k + \frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{a_k(z_k^Tq_k)^2}$$

$$S_{k+1} = S_k + \frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{q_k^Tp_k - q_k^TS_kq_k}$$

$$S_{k+1} = S_k + \frac{(p_k - S_k q_k)(p_k - S_k q_k)^T}{q_k^T(p_k - S_kq_k)}$$

$$z_k = p_k - S_k q_k, \;\; a_k=\frac{1}{q_k^T(p_k - S_kq_k)}$$


## Task 2
![](https://i.imgur.com/IiJqQJx.png)

$$x_{i+1} = x_i - \alpha_i f'(x_i) - \beta_i(x_i - x_{i-1})$$
where $\alpha, \beta$ minimize f on a plane. 
A is positive definite.

$$f(x) = \frac{1}{2}\langle Ax, x \rangle - \langle b, x \rangle = \langle \frac{1}{2}Ax - b, x \rangle$$

$$f'(x_i) = Ax_i-b = r_{i+1}$$

$$〈r_{i+1}, d_j 〉 = 0 \;\;for \;\;j = 1, . . . , i.$$

$$〈r_{i+1}, Av〉 = 0 \;\; for \;\; v \in lin\{{d_1, \ldots, d_{i-1}}\}$$

![](https://i.imgur.com/ynyJRqW.png)

$$\frac{\partial f}{\partial x} = \frac{1}{2}\langle Ax, x \rangle' - \langle b, x \rangle' = \frac{1}{2}(\langle Ax', x \rangle + \langle Ax, x' \rangle) - (\langle b, x' \rangle + \langle b', x \rangle) =\\=\frac{1}{2}(\langle x', Ax \rangle + \langle Ax, x' \rangle) - \langle b, x' \rangle=\langle Ax, x' \rangle - \langle b, x' \rangle = \langle Ax - b, x' \rangle$$

In normal CG:
$$x_i = x_{i-1} - \frac{\langle r_{i}, r_{i} \rangle}{\langle Ad_i, d_i \rangle} d_i = x_{i-1} + \frac{-\langle r_{i}, d_i \rangle}{\langle Ad_i, d_i \rangle} d_i = x_{i-1} - \gamma_i d_i$$

So we want to minimize:
$$\min_{\alpha_i, \beta_i} \phi(\alpha_i,\beta_i) = \min_{\alpha, \beta} f(x_i - \alpha_i r_{i+1} - \beta_i(x_i - x_{i-1}))$$

$$f(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) = \langle \frac{1}{2}A(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i), (x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) \rangle - \langle b, (x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) \rangle$$

$$\frac{\partial \phi}{\partial \alpha_i} = \langle Ax - b, x' \rangle = \langle A(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) - b, (x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i)' \rangle
=\\= 
\langle A(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) - b, -r_{i+1}\rangle 
=\\=
\langle Ax_i, -r_{i+1}\rangle - \alpha_i\langle Ar_{i+1}, -r_{i+1}\rangle + \langle \beta_i\gamma_iAd_i, -r_{i+1}\rangle  - \langle b, -r_{i+1} \rangle
= \\=
-\langle Ax_i, r_{i+1}\rangle + \alpha_i\langle Ar_{i+1}, r_{i+1}\rangle - \langle \beta_i\gamma_iAd_i, r_{i+1}\rangle + \langle b,r_{i+1} \rangle = 0$$

$$\alpha_i = \frac{\langle Ax_i, r_{i+1}\rangle - \langle b,r_{i+1} \rangle+ \langle \beta_i\gamma_iAd_i, r_{i+1}\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle} = \frac{\langle r_{i+1}, r_{i+1}\rangle - \langle \beta_iA(x_i - x_{i-1}), r_{i+1}\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle}$$

$$\frac{\partial \phi}{\partial \beta_i} = \langle Ax - b, x' \rangle = \langle A(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) - b, (x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i)' \rangle 
=\\=
\langle A(x_i - \alpha_i r_{i+1} + \beta_i\gamma_id_i) - b, \gamma_id_i\rangle = \langle Ax_i, \gamma_id_i\rangle - \langle \alpha_iAr_{i+1}, \gamma_id_i\rangle + \beta_i\langle \gamma_iAd_i, \gamma_id_i\rangle - \langle b,\gamma_id_i \rangle = 0$$

$$\beta_i = \frac{-\langle Ax_i, \gamma_id_i\rangle +\langle b,\gamma_id_i \rangle+ \langle \alpha_iAr_{i+1}, \gamma_id_i\rangle}{\langle \gamma_iAd_i, \gamma_id_i\rangle} =\frac{\langle r_{i+1}, (x_i - x_{i-1})\rangle - \langle \alpha_iAr_{i+1}, (x_i - x_{i-1})\rangle}{\langle A(x_i - x_{i-1}), (x_i - x_{i-1})\rangle}
=\\=
\frac{-\langle r_{i+1}, d_i\rangle + \langle \alpha_iAr_{i+1},d_i\rangle}{\langle Ad_i, \gamma_id_i\rangle} = \frac{\langle \alpha_iAr_{i+1},d_i\rangle}{\langle Ad_i, \gamma_id_i\rangle}$$

$$\beta_i = \alpha_i\frac{\langle Ar_{i+1},d_i\rangle}{\gamma_i\langle Ad_i, d_i\rangle}$$

$$\alpha_i = \frac{\langle r_{i+1}, r_{i+1}\rangle + \langle \beta_i\gamma_iAd_i, r_{i+1}\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle} = \frac{\langle r_{i+1}, r_{i+1}\rangle + \alpha_i\langle Ar_{i+1},d_i\rangle\langle \gamma_iAd_i, r_{i+1}\rangle / \gamma_i\langle Ad_i, d_i\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle}
=\\=
\frac{\langle r_{i+1}, r_{i+1}\rangle + \alpha_i\langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle / \langle Ad_i, d_i\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle}
$$


$$\alpha_i \langle Ar_{i+1}, r_{i+1}\rangle = \langle r_{i+1}, r_{i+1}\rangle + \frac{\alpha_i\langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}{\langle Ad_i, d_i\rangle}$$


$$\alpha_i \langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle = \langle r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle + \alpha_i\langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle$$

$$\alpha_i = \frac{\langle r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle}{ \langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}$$

$$\beta_i = \alpha_i\frac{\langle Ar_{i+1},d_i\rangle}{\gamma_i\langle Ad_i, d_i\rangle} = \frac{\langle Ar_{i+1},d_i\rangle \langle r_{i+1}, r_{i+1}\rangle}{\gamma_i( \langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle)}$$


$$x_{i+1} = x_i - \alpha_i r_{i+1} - \beta_i(x_i - x_{i-1}) 
=\\=
x_i - \frac{\langle r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle}{ \langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle} r_{i+1} + \frac{\langle Ar_{i+1},d_i\rangle \langle r_{i+1}, r_{i+1}\rangle}{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle }d_i
=\\=
x_i - \frac{\langle Ar_{i+1},d_i\rangle \langle r_{i+1}, r_{i+1}\rangle d_i - \langle r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle r_{i+1}}{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}
=\\=
x_i - \frac{\langle r_{i+1}, r_{i+1}\rangle(\langle Ar_{i+1},d_i\rangle  d_i - \langle Ad_i, d_i\rangle r_{i+1})}{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}
=\\=
x_i - \frac{\langle r_{i+1}, r_{i+1}\rangle\langle Ad_i, d_i\rangle(\frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i -  r_{i+1})}{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}
=\\=
x_i - \frac{\langle r_{i+1}, r_{i+1}\rangle\langle Ad_i, d_i\rangle }{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}d_{i+1}
$$

We just need to show now, that 
$$
\frac{\langle Ar_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle\langle Ad_i, r_{i+1}\rangle}{\langle Ad_i, d_i\rangle} = \langle Ad_{i+1}, d_{i+1}\rangle
$$
Just for reminder:
$$
d_{i+1} = \frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i -  r_{i+1}
$$

$$
\langle Ad_{i+1}, d_{i+1}\rangle = \langle A(\frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i -  r_{i+1}), \frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i -  r_{i+1}\rangle
=\\=
\langle A\frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i, \frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i\rangle - 
\langle A\frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i, r_{i+1}\rangle -
\langle A r_{i+1}, \frac{\langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle}  d_i\rangle +
\langle A r_{i+1}, r_{i+1}\rangle
=\\=
\frac{\langle Ar_{i+1},d_i\rangle \langle Ar_{i+1},d_i\rangle \langle Ad_i, d_i\rangle}{\langle Ad_i, d_i\rangle \langle Ad_i, d_i\rangle} - 
\frac{\langle Ar_{i+1},d_i\rangle \langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle} - 
\frac{\langle Ar_{i+1},d_i\rangle \langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle} +
\langle A r_{i+1}, r_{i+1}\rangle
=\\= -
\frac{\langle Ar_{i+1},d_i\rangle  \langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle } + \langle A r_{i+1}, r_{i+1}\rangle =
-\frac{\langle Ar_{i+1},d_i\rangle  \langle Ar_{i+1},d_i\rangle - \langle A r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle}{\langle Ad_i, d_i\rangle }
=\\=
\frac{\langle A r_{i+1}, r_{i+1}\rangle \langle Ad_i, d_i\rangle - \langle Ar_{i+1},d_i\rangle  \langle Ar_{i+1},d_i\rangle}{\langle Ad_i, d_i\rangle }
$$

Using above result we get:
$$
x_{i+1} = x_i - \frac{\langle r_{i+1}, r_{i+1}\rangle}{\langle Ad_{i+1}, d_{i+1}\rangle}d_{i+1}
$$