from scipy.integrate import solve_ivp

def van_der_pol(t, y):
    return [y[1], (1.0 - y[0] * y[0]) * y[1] - y[0]]

def lotka_volterra(t, y):
    return [1.5 * y[0] - y[0] * y[1], y[0] * y[1] - 3.0 * y[1]]

def reference(name, f, t1, y0):
    sol = solve_ivp(f, (0.0, t1), y0, method="DOP853", rtol=1e-13, atol=1e-13)
    print(name, "t =", t1)
    for i, v in enumerate(sol.y[:, -1]):
        print("y%d = %.15f" % (i + 1, v))
    rk45 = solve_ivp(f, (0.0, t1), y0, method="RK45", rtol=1e-9, atol=1e-12)
    print("scipy RK45 rtol=1e-9: nfev =", rk45.nfev, "steps =", len(rk45.t) - 1)
    for i, v in enumerate(rk45.y[:, -1]):
        print("y%d = %.15f, err = %.3e" % (i + 1, v, abs(v - sol.y[i, -1])))

reference("van der pol", van_der_pol, 20.0, [2.0, 0.0])
reference("lotka-volterra", lotka_volterra, 15.0, [10.0, 5.0])
