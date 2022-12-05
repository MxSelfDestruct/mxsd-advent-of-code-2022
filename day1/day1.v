import os

fn main() {
	data := os.read_lines("input.txt")!

	mut total := 0
	mut totals := []int{}

	for line in data {
		if line == "" {
			totals << total
			total = 0
		}

		else {
			total += line.int()
		}
	}

	high1 := pop_highest_int(mut totals)
	high2 := pop_highest_int(mut totals)
	high3 := pop_highest_int(mut totals)

	println("Highest calorie totals:")
	println("1:\t${high1}")
	println("2:\t${high2}")
	println("3:\t${high3}")
	println("Total:\t${high1 + high2 + high3}")
}

fn pop_highest_int(mut arr []int) int {
	mut highest := 0
	mut highest_index := 0

	for i, num in arr {
		if num > highest {
			highest = num
			highest_index = i
		}
	}

	arr[highest_index] = 0
	return highest
}