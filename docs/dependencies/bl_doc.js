hljs.registerLanguage('bl', function(hljs) {
  return {
    name: 'BhauLang',
    keywords: {
      keyword: 'bhau hai ahe bhau jar bhau nahitar bhau tar bhau joparent bhau lakshat thev bhau parat de hi bhau bye bhau bhau chunav bhau nivad bhau thamb bhau chalu rha bhau rahudet bhau baherun ghe bhau ithun chalu ptr ref',
      literal: 'khara khota'
    },
    contains: [
      hljs.C_LINE_COMMENT_MODE,
      hljs.C_BLOCK_COMMENT_MODE,
      hljs.QUOTE_STRING_MODE,
      hljs.NUMBER_MODE
    ]
  };
});

hljs.highlightAll();


document.querySelectorAll(".sidebar a").forEach(link => {
  link.addEventListener("click", e => {
    e.preventDefault();
    const page = link.dataset.page;
    document.querySelectorAll(".page").forEach(p => p.classList.remove("active"));
    document.getElementById(page).classList.add("active");
  });
});