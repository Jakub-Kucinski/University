import numpy as np
import scipy.stats

def classification(x):
    targets = np.loadtxt('ImageExpertReduced.txt')
    rules = np.loadtxt('ClassificationRules.txt')
    rules_indices = np.where(x == 1)
    values_of_rules = rules[rules_indices, :][0]
    return np.sum(scipy.stats.mode(values_of_rules, axis=0)[0][0] == targets)