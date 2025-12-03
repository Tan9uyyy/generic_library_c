

T       B_TREE_METHOD(new) (void);
int     B_TREE_METHOD(is_empty) (T b_tree);
T       B_TREE_METHOD(push) (T b_tree, b_tree_datum_t value);
T       B_TREE_METHOD(pop) (T b_tree, b_tree_datum_t value);
T       B_TREE_METHOD(pop_small) (T b_tree, b_tree_datum_t *value);
T       B_TREE_METHOD(pop_big) (T b_tree, b_tree_datum_t *value);
int     B_TREE_METHOD(contains) (T b_tree, b_tree_datum_t value);
T       B_TREE_METHOD(delete) (T b_tree);
void    B_TREE_METHOD(print) (T b_tree);