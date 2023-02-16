def HITS(g,authority={},hubs={}):
    MaxIterator=100  #最大迭代次数
    Convergency=0.001        #迭代结束的条件,判断是否收敛
    graph=g
    #初始化字典
    for node in graph.nodes():
        authority[node]=1
        hubs[node]=1

    for iter in range(MaxIterator):  # 迭代
        d_value = 0.0
        norm_a = 0  # 标准化
        norm_h = 0

        item_a = authority.copy()  # 保存上一次的值，在下面算差值时用到
        for node in graph.nodes():
            authority[node] = 0
            for incident in graph.in_edges(node):
                authority[node] += hubs[incident[0]]
            norm_a += pow(authority[node], 2)
        for node in graph.nodes():
            authority[node] /= norm_a
            d_value += abs(item_a[node] - authority[node])  # 计算差值，判断是否收敛

        item_h = hubs.copy()
        for node in graph.nodes():
            hubs[node] = 0
            for neighbor in graph.neighbors(node):
                hubs[node] += authority[neighbor]
            norm_h += pow(hubs[node], 2)
        for node in graph.nodes():
            hubs[node] /= norm_h
            d_value += abs(item_h[node] - hubs[node])
        if d_value < Convergency:
            break
    return authority, hubs

