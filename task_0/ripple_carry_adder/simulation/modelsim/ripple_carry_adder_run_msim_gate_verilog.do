transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vlog -vlog01compat -work work +incdir+. {ripple_carry_adder.vo}

vlog -vlog01compat -work work +incdir+C:/Users/sanjana\ MR/OneDrive/Desktop/tasks/p2 {C:/Users/sanjana MR/OneDrive/Desktop/tasks/p2/ripple_carry_adder_test_bench.v}

vsim -t 1ps -L altera_ver -L cycloneive_ver -L gate_work -L work -voptargs="+acc"  ripple_carry_adder_test_bench

add wave *
view structure
view signals
run -all
