transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/sanjana\ MR/OneDrive/Desktop/tasks/p2 {C:/Users/sanjana MR/OneDrive/Desktop/tasks/p2/ripple_carry_adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/sanjana\ MR/OneDrive/Desktop/tasks/p2 {C:/Users/sanjana MR/OneDrive/Desktop/tasks/p2/full_adder.v}

vlog -vlog01compat -work work +incdir+C:/Users/sanjana\ MR/OneDrive/Desktop/tasks/p2 {C:/Users/sanjana MR/OneDrive/Desktop/tasks/p2/ripple_carry_adder_test_bench.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  ripple_carry_adder_test_bench

add wave *
view structure
view signals
run -all
