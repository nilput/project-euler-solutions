.PHONY: clean
clean:
	find . -perm +0100 -type f -and -not -path '*.git*' -exec 'rm' '{}' ';'
