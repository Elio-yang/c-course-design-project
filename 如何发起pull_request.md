1. 先 fork 别人的仓库，相当于拷贝一份，相信我，不会有人直接让你改修原仓库的
2. clone 到本地分支，做一些 bug fix
3. 发起 pull request 给原仓库，让他看到你修改的 bug
4. 原仓库 review 这个 bug，如果是正确的话，就会 merge 到他自己的项目中

至此，整个 pull request 的过程就结束了。

理解了 pull request 的含义和流程，具体操作也就简单了。以 Github 排名最高的 [https://github.com/twbs/bootstrap](https://link.zhihu.com/?target=https%3A//github.com/twbs/bootstrap) 为例说明。

1. 先点击 fork 仓库，项目现在就在你的账号下了



![img](https://pic1.zhimg.com/50/0d01d6aa4cc4330c525347e5b0a0ecb8_hd.jpg?source=1940ef5c)![img](https://pic1.zhimg.com/80/0d01d6aa4cc4330c525347e5b0a0ecb8_720w.jpg?source=1940ef5c)



![img](https://pic4.zhimg.com/50/6aaed35908e74de871fcbed7c5affb0e_hd.jpg?source=1940ef5c)![img](https://pic4.zhimg.com/80/6aaed35908e74de871fcbed7c5affb0e_720w.jpg?source=1940ef5c)



2. 在你自己的机器上 git clone 这个仓库，切换分支（也可以在 master 下），做一些修改。

```bash
~  git clone https://github.com/beepony/bootstrap.git
~  cd bootstrap
~  git checkout -b test-pr
~  git add . && git commit -m "test-pr"
~  git push origin test-pr
```

3. 完成修改之后，回到 test-pr 分支，点击旁边绿色的 Compare & pull request 按钮

![img](https://pic4.zhimg.com/50/3e1ac7f58774a79a5dd6bf8e852e4199_hd.jpg?source=1940ef5c)![img](https://pic4.zhimg.com/80/3e1ac7f58774a79a5dd6bf8e852e4199_720w.jpg?source=1940ef5c)

4. 添加一些注释信息，确认提交

![img](https://pic1.zhimg.com/50/f5ed68dfe4d60fe90e2fb22ec1933006_hd.jpg?source=1940ef5c)![img](https://pic1.zhimg.com/80/f5ed68dfe4d60fe90e2fb22ec1933006_720w.jpg?source=1940ef5c)

5. 仓库作者看到，你提的确实是对的，就会 merge，合并到他的项目中