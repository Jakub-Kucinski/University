def number_of_coins(amount, coin):
    counter = 0
    while amount - coin >= 0:
        counter += 1
        amount -= coin
    return counter


def optimal_money(amount):
    list_of_coins = [20, 10, 5, 2, 1]
    dict_of_coins = {}
    for coin in list_of_coins:
        count = number_of_coins(amount, coin)
        dict_of_coins[f"{coin}zł"] = count
        amount -= count * coin
    return dict_of_coins


print(optimal_money(123))
