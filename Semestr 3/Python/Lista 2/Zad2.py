class Formula:
    pass


class TrueForm(Formula):
    def __init__(self):
        pass

    def calculate(self, variables):
        return True

    def variables_in_formula(self):
        return []

    def __str__(self):
        return "true"


class FalseForm(Formula):
    def __init__(self):
        pass

    def calculate(self, variables):
        return False

    def variables_in_formula(self):
        return []

    def __str__(self):
        return "false"


class Variable(Formula):
    def __init__(self, name):
        self.name = name

    def calculate(self, variables):
        return variables[self.name]

    def variables_in_formula(self):
        return [self.name]

    def __str__(self):
        return self.name


class And(Formula):
    def __init__(self, formula1, formula2):
        self.formula1 = formula1
        self.formula2 = formula2

    def calculate(self, variables):
        val1 = self.formula1.calculate(variables)
        val2 = self.formula2.calculate(variables)
        return val1 and val2

    def variables_in_formula(self):
        var1 = self.formula1.variables_in_formula()
        var2 = self.formula2.variables_in_formula()
        return list(set(var1 + var2))

    def __str__(self):
        f1 = self.formula1.__str__()
        f2 = self.formula2.__str__()
        return '(' + f1 + " ∧ " + f2 + ')'


class Or(Formula):
    def __init__(self, formula1, formula2):
        self.formula1 = formula1
        self.formula2 = formula2

    def calculate(self, variables):
        val1 = self.formula1.calculate(variables)
        val2 = self.formula2.calculate(variables)
        return val1 or val2

    def variables_in_formula(self):
        var1 = self.formula1.variables_in_formula()
        var2 = self.formula2.variables_in_formula()
        return list(set(var1+var2))

    def __str__(self):
        f1 = self.formula1.__str__()
        f2 = self.formula2.__str__()
        return '(' + f1 + " ∨ " + f2 + ')'


class Impl(Formula):
    def __init__(self, formula1, formula2):
        self.formula1 = formula1
        self.formula2 = formula2

    def calculate(self, variables):
        val1 = self.formula1.calculate(variables)
        val2 = self.formula2.calculate(variables)
        return not val1 or val2

    def variables_in_formula(self):
        var1 = self.formula1.variables_in_formula()
        var2 = self.formula2.variables_in_formula()
        return list(set(var1 + var2))

    def __str__(self):
        f1 = self.formula1.__str__()
        f2 = self.formula2.__str__()
        return '(' + f1 + " => " + f2 + ')'


class Not(Formula):
    def __init__(self, formula):
        self.formula = formula

    def calculate(self, variables):
        return not (self.formula.calculate(variables))

    def variables_in_formula(self):
        return self.formula.variables_in_formula()

    def __str__(self):
        return "not" + self.formula.__str__()


def is_tauto(formula):
    def valuations(partial_valuations, n):
        if (n <= 0):
            return partial_valuations
        # print(partial_valuations)
        val_ending_with_0 = [valuation+[0] for valuation in partial_valuations]
        val_ending_with_1 = [valuation+[1] for valuation in partial_valuations]
        # print(valuations_ending_with_0)
        # print(valuations_ending_with_1)
        # print("------")
        new_partial_valuations = val_ending_with_0 + val_ending_with_1
        return valuations(new_partial_valuations, n-1)

    list_of_variables = formula.variables_in_formula()
    # print(list_of_variables)
    # print(len(list_of_variables))
    if (list_of_variables == []):
        return formula.calculate({})
    number_of_variables = len(list_of_variables)
    list_of_valuations = valuations([[]], number_of_variables)

    for valuation in list_of_valuations:
        variables_with_valuations = dict(zip(list_of_variables, valuation))
        if (not formula.calculate(variables_with_valuations)):
            return (False, variables_with_valuations)
    return True


variables = {"x": True, "y": False}
formula = Impl(Variable("x"), And(Variable("y"), TrueForm()))
tautology1 = Impl(Variable("x"), Variable("x"))
tautology2 = Impl(FalseForm(), Variable("x"))
not_tautology3 = Impl(TrueForm(), Variable("x"))
tautology4 = Or(Variable("x"), Not(Variable("x")))
print(formula.calculate(variables))
print(formula.variables_in_formula())
print(is_tauto(formula))
print(is_tauto(tautology1))
print(is_tauto(tautology2))
print(is_tauto(not_tautology3))
print(is_tauto(tautology4))
print(formula)