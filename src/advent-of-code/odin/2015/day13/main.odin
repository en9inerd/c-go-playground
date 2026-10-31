package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"


Entry :: struct {
	a:     int,
	b:     int,
	value: int,
}


get_name_id :: proc(names: ^map[string]int, count: ^int, name: string) -> int {
	if id, ok := names^[name]; ok {
		return id
	}

	id := count^
	names^[name] = id
	count^ += 1

	return id
}


parse_input :: proc(data: string) -> (map[string]int, [dynamic]Entry, int) {
	names := make(map[string]int)
	entries := make([dynamic]Entry)

	name_count := 0

	for raw_line in strings.split(data, "\n") {
		line := strings.trim_space(raw_line)

		if line == "" {
			continue
		}

		words := strings.fields(line)

		a_name := words[0]

		value, err := strconv.parse_int(words[3])
		if err != true {
			continue
		}

		if words[2] == "lose" {
			value = -value
		}

		b_name := strings.trim_right(words[10], ".")

		a := get_name_id(&names, &name_count, a_name)
		b := get_name_id(&names, &name_count, b_name)

		append(&entries, Entry{a = a, b = b, value = value})
	}

	return names, entries, name_count
}


max_happiness :: proc(entries: []Entry, n: int) -> int {
	happiness := make([]int, n * n, context.allocator)

	for e in entries {
		happiness[e.a * n + e.b] = e.value
	}


	states := 1 << u64(n - 1)

	NEG_INF :: -1 << 60

	dp := make([]int, states * n, context.allocator)

	for i in 0 ..< len(dp) {
		dp[i] = NEG_INF
	}


	// Person 0 is fixed.
	for i in 1 ..< n {
		mask := 1 << u64(i - 1)

		dp[mask * n + i] = happiness[0 * n + i] + happiness[i * n + 0]
	}


	for mask in 0 ..< states {
		for last in 1 ..< n {

			current := dp[mask * n + last]

			if current == NEG_INF {
				continue
			}


			for next in 1 ..< n {

				bit := 1 << u64(next - 1)

				if mask & bit != 0 {
					continue
				}


				new_mask := mask | bit

				gain := happiness[last * n + next] + happiness[next * n + last]

				index := new_mask * n + next

				candidate := current + gain

				if candidate > dp[index] {
					dp[index] = candidate
				}
			}
		}
	}


	answer := NEG_INF
	full := states - 1

	for last in 1 ..< n {
		candidate := dp[full * n + last] + happiness[last * n + 0] + happiness[0 * n + last]

		if candidate > answer {
			answer = candidate
		}
	}

	return answer
}


main :: proc() {
	data, err := os.read_entire_file_from_path("input.txt", context.allocator)

	if err != nil {
		fmt.println(err)
		return
	}


	_, entries, count := parse_input(string(data))

	result := max_happiness(entries[:], count)

	fmt.println(result)
}
