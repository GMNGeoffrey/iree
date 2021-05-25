func @dynamic_update_slice() attributes { iree.module.export } {
  %target = iree.unfoldable_constant dense<2> : tensor<3x3xi32>
  %update = iree.unfoldable_constant dense<1> : tensor<2x2xi32>
  %c0 = iree.unfoldable_constant dense<0> : tensor<i32>
  %result = "mhlo.dynamic-update-slice"(%target, %update, %c0, %c0)
    : (tensor<3x3xi32>, tensor<2x2xi32>, tensor<i32>, tensor<i32>) -> tensor<3x3xi32>
  check.expect_eq_const(%result, dense<[
    [2, 2, 2],
    [2, 2, 2],
    [2, 2, 2]]> : tensor<3x3xi32>) : tensor<3x3xi32>
  return
}
