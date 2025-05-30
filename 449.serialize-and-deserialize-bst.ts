/*
 * @lc app=leetcode id=449 lang=typescript
 *
 * [449] Serialize and Deserialize BST
 */

declare class TreeNode {
    val: number
    left: TreeNode | null
    right: TreeNode | null
    constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null)
}

// @lc code=start

function serialize(root: TreeNode | null): string {
    const res: number[] = []
    const stack: TreeNode[] = []
    let node = root
    while (node || stack.length) {
        while (node) {
            stack.push(node)
            node = node.left
        }
        node = stack.pop()!
        res.push(node.val)
        node = node.right
    }
    return res.join(',')
};

function deserialize(data: string): TreeNode | null {
    if (!data) return null
    const nums = data.split(',').map(Number)
    const root = new TreeNode(nums[0])
    for (let i = 1; i < nums.length; i++) {
        insert(root, nums[i])
    }
    return root
};

function insert(root: TreeNode, v: number): void {
    let cur = root
    while (true) {
        if (v < cur.val) {
            if (cur.left) cur = cur.left
            else { cur.left = new TreeNode(v); break }
        } else {
            if (cur.right) cur = cur.right
            else { cur.right = new TreeNode(v); break }
        }
    }
}

/**
 * Your functions will be called as such:
 * deserialize(serialize(root));
 */
// @lc code=end

