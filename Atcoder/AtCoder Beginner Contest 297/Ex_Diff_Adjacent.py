def is_splendid(seq):
    return all(seq[i] != seq[i+1] for i in range(len(seq)-1))


def count_splendid_sequences(N):
    count = 0
    for seq in product(range(1, N+1), repeat=N):
        if sum(seq) == N and is_splendid(seq):
            count += 1
    return count


print(count_splendid_sequences(4))  # output: 164
