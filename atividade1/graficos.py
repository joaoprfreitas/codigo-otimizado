import matplotlib.pyplot as plt
import numpy as np

def main():
    labels = ['Sem otimização', 'Loop Interchange', 'Loop Unrolling']

    # metrica 1 l1-load
    # matrix100 = [22806361, 22800872, 21306754]
    # matrix1000 = [22061876614, 22061441785, 20562177136]

    # metrica 2 l1-miss
    # matrix100 = [80259, 81902, 81419]
    # matrix1000 = [1189234992, 64226241, 1189324577]

    # metrica 3 branch
    # matrix100 = [1550061, 1546854, 1050426]
    # matrix1000 = [1039836968, 1039604230, 540052568]
    
    # metrica 4 branch miss
    matrix100 =  [17901,17701,7912]
    matrix1000 = [1107455,1103600,1115887]
    

    x = np.arange(len(labels))
    width = 0.3

    plt.figure(figsize=(12,5))

    plt.subplot(121)
    plt.title('Matrix 100x100', fontsize=18)
    plt.bar(x, matrix100, width, label='test1')
    plt.xticks([0,1,2], labels, fontsize=10)
    plt.ylabel('branch-misses', fontsize=10)    
    plt.text(0, matrix100[0], str(matrix100[0]), ha='center', va='bottom', fontsize=10)
    plt.text(1, matrix100[1], str(matrix100[1]), ha='center', va='bottom', fontsize=10)
    plt.text(2, matrix100[2], str(matrix100[2]), ha='center', va='bottom', fontsize=10)

    plt.subplot(122)
    plt.title('Matrix 1000x1000', fontsize=18)
    plt.bar(x, matrix1000, width)
    plt.xticks([0,1,2], labels, fontsize=10)
    plt.ylabel('branch-misses', fontsize=10)
    plt.text(0, matrix1000[0], str(matrix1000[0]), ha='center', va='bottom', fontsize=10)
    plt.text(1, matrix1000[1], str(matrix1000[1]), ha='center', va='bottom', fontsize=10)
    plt.text(2, matrix1000[2], str(matrix1000[2]), ha='center', va='bottom', fontsize=10)

    plt.figlegend(loc='upper right', ncol=1, labelspacing=0.5, fontsize=14, bbox_to_anchor=(1.11, 0.9))
    plt.tight_layout(w_pad=6)
    plt.show()
    plt.savefig("branch-misses.png")

if __name__ == '__main__':
    main()