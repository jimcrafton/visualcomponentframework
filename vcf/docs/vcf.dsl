<!DOCTYPE style-sheet PUBLIC
          "-//James Clark//DTD DSSSL Style Sheet//EN" [
<!ENTITY % html "INCLUDE">
<![%html;[
<!ENTITY docbook.dsl PUBLIC
         "-//Norman Walsh//DOCUMENT DocBook HTML Stylesheet//EN"
         CDATA dsssl>
]]>
<!ENTITY % online "INCLUDE">
<![%online;[
<!ENTITY docbook.dsl PUBLIC
         "-//Norman Walsh//DOCUMENT DocBook Print Stylesheet//EN"
         CDATA dsssl>
]]>
]>

<style-sheet>
<!--
;; customize the html stylesheet; parts borrowed from 
;; Cygnus at http://sourceware.cygnus.com/ (cygnus-both.dsl)
-->

<style-specification id="online" use="docbook">
<style-specification-body> 

(declare-characteristic preserve-sdata?
  ;; this is necessary because right now jadetex does not understand
  ;; symbolic entities, whereas things work well with numeric entities.
  "UNREGISTERED::James Clark//Characteristic::preserve-sdata?"
  #f)

(declare-flow-object-class element
  ;; for redhat
  "UNREGISTERED::James Clark//Flow Object Class::element")

(define %generate-legalnotice-link%
  ;; put the legal notice in a separate file
  #t)

(define %admon-graphics-path%
  ;; use graphics in admonitions, set their
  "../images/")

(define %admon-graphics%
  #t)

(define %funcsynopsis-decoration%
  ;; make funcsynopsis look pretty
  #t)

(define %html-ext%
  ;; when producing HTML files, use this extension
  ".html")

(define %generate-book-toc%
  ;; Should a Table of Contents be produced for books?
  #t)

(define %generate-article-toc% 
  ;; Should a Table of Contents be produced for articles?
  #t)

(define %generate-part-toc%
  ;; Should a Table of Contents be produced for parts?
  #t)

(define %generate-book-titlepage%
  ;; produce a title page for books
  #t)

(define %generate-article-titlepage%
  ;; produce a title page for articles
  #t)

(define (chunk-skip-first-element-list)
  ;; forces the Table of Contents on separate page
  '())

(define (list-element-list)
  ;; fixes bug in Table of Contents generation
  '())

(define %root-filename%
  ;; The filename of the root HTML document (e.g, "index").
  "index")

(define %shade-verbatim%
  ;; verbatim sections will be shaded if t(rue)
  #t)

(define %use-id-as-filename%
  ;; Use ID attributes as name for component HTML files?
  #t)

(define %graphic-extensions%
  ;; graphic extensions allowed
  '("gif" "png" "jpg" "jpeg" "tif" "tiff" "eps" "epsf" ))

(define %graphic-default-extension% 
  "gif")

(define %section-autolabel%
  ;; For enumerated sections (1.1, 1.1.1, 1.2, etc.)
  #t)

(define (toc-depth nd)
  ;; more depth (2 levels) to toc; instead of flat hierarchy
  2)

(element emphasis
  ;; make role=strong equate to bold for emphasis tag
  (if (equal? (attribute-string "role") "strong")
     (make element gi: "STRONG" (process-children))
     (make element gi: "EM" (process-children))))

(define (book-titlepage-recto-elements)
  ;; elements on a book's titlepage
  (list (normalize "title")
        (normalize "subtitle")
        (normalize "graphic")
        (normalize "mediaobject")
        (normalize "corpauthor")
        (normalize "authorgroup")
        (normalize "author")
        (normalize "othercredit")
        (normalize "edition")
        (normalize "releaseinfo")
        (normalize "publisher")
        (normalize "editor")
        (normalize "copyright")
        (normalize "pubdate")
        (normalize "revhistory")
        (normalize "abstract")
        (normalize "legalnotice")))

(define (article-titlepage-recto-elements)
  ;; elements on an article's titlepage
  (list (normalize "title")
        (normalize "subtitle")
        (normalize "authorgroup")
        (normalize "author")
        (normalize "othercredit")
        (normalize "releaseinfo")
        (normalize "copyright")
        (normalize "pubdate")
        (normalize "revhistory")
        (normalize "abstract")
        (normalize "legalnotice")))

(define (process-contrib #!optional (sosofo (process-children)))
  ;; print out with othercredit information; for translators, etc.
  (make sequence
    (make element gi: "SPAN"
          attributes: (list (list "CLASS" (gi)))
          (process-children))))

(define (process-othercredit #!optional (sosofo (process-children)))
  ;; print out othercredit information; for translators, etc.
  (let ((author-name  (author-string))
        (author-contrib (select-elements (children (current-node))
                                          (normalize "contrib"))))
    (make element gi: "P"
         attributes: (list (list "CLASS" (gi)))
         (make element gi: "B"
              (literal author-name)
              (literal " - "))
         (process-node-list author-contrib))))

(mode article-titlepage-recto-mode
  (element contrib (process-contrib))
  (element othercredit (process-othercredit))
)

(mode book-titlepage-recto-mode
  (element contrib (process-contrib))
  (element othercredit (process-othercredit))
)

(define (article-title nd)
  (let* ((artchild  (children nd))
         (artheader (select-elements artchild (normalize "artheader")))
         (artinfo   (select-elements artchild (normalize "articleinfo")))
         (ahdr (if (node-list-empty? artheader)
                   artinfo
                   artheader))
         (ahtitles  (select-elements (children ahdr)
                                     (normalize "title")))
         (artitles  (select-elements artchild (normalize "title")))
         (titles    (if (node-list-empty? artitles)
                        ahtitles
                        artitles)))
    (if (node-list-empty? titles)
        ""
        (node-list-first titles))))

(mode subtitle-mode
  ;; do not print subtitle on subsequent pages
  (element subtitle (empty-sosofo)))

;; Redefinition of $verbatim-display$
;; Origin: dbverb.dsl
;; Different foreground and background colors for verbatim elements
;; Author: Philippe Martin (feloy@free.fr) 2001-04-07

(define ($verbatim-display$ indent line-numbers?)
  (let ((verbatim-element (gi))
        (content (make element gi: "PRE"
                       attributes: (list
                                    (list "CLASS" (gi)))
                       (if (or indent line-numbers?)
                           ($verbatim-line-by-line$ indent line-numbers?)
                           (process-children)))))
    (if %shade-verbatim%
        (make element gi: "TABLE"
              attributes: (shade-verbatim-attr-element verbatim-element)
              (make element gi: "TR"
                    (make element gi: "TD"
                          (make element gi: "FONT" 
                                attributes: (list
                                             (list "COLOR" (car (shade-verbatim-element-colors
                                                                 verbatim-element))))
                                content))))
        content)))

;;
;; Customize this function
;; to change the foreground and background colors
;; of the different verbatim elements
;; Return (list "foreground color" "background color")
;;
(define (shade-verbatim-element-colors element)
  (case element
    (("SYNOPSIS") (list "#000000" "#6495ED"))
    ;; ...
    ;; Add your verbatim elements here
    ;; ...
    (else (list "#000000" "#E0E0E0"))))

(define (shade-verbatim-attr-element element)
  (list
  (list "BORDER" 
	(cond
		((equal? element (normalize "SCREEN")) "1")
		(else "0")))
   (list "BGCOLOR" (car (cdr (shade-verbatim-element-colors element))))
   (list "WIDTH" ($table-width$))))

;; End of $verbatim-display$ redefinition

</style-specification-body>
</style-specification>

<!--
;; customize the html stylesheet; parts borrowed from 
;; Cygnus at http://sourceware.cygnus.com/ (cygnus-both.dsl)
-->

<style-specification id="html" use="docbook">
<style-specification-body> 

(define %stylesheet% "vcf.css")



(declare-characteristic preserve-sdata?
  ;; this is necessary because right now jadetex does not understand
  ;; symbolic entities, whereas things work well with numeric entities.
  "UNREGISTERED::James Clark//Characteristic::preserve-sdata?"
  #f)

(declare-flow-object-class element
  ;; for redhat
  "UNREGISTERED::James Clark//Flow Object Class::element")

(define %generate-legalnotice-link%
  ;; put the legal notice in a separate file
  #t)

(define %admon-graphics-path%
  ;; use graphics in admonitions, set their
  "../images/")

(define %admon-graphics%
  #t)

(define %funcsynopsis-decoration%
  ;; make funcsynopsis look pretty
  #t)

(define %html-ext%
  ;; when producing HTML files, use this extension
  ".html")

(define %generate-book-toc%
  ;; Should a Table of Contents be produced for books?
  #t)

(define %generate-article-toc% 
  ;; Should a Table of Contents be produced for articles?
  #t)

(define %generate-part-toc%
  ;; Should a Table of Contents be produced for parts?
  #t)

(define %generate-book-titlepage%
  ;; produce a title page for books
  #t)

(define %generate-article-titlepage%
  ;; produce a title page for articles
  #t)

(define (chunk-skip-first-element-list)
  ;; forces the Table of Contents on separate page
  '())

(define (list-element-list)
  ;; fixes bug in Table of Contents generation
  '())

(define %root-filename%
  ;; The filename of the root HTML document (e.g, "index").
  "index")

(define %shade-verbatim%
  ;; verbatim sections will be shaded if t(rue)
  #t)

(define %use-id-as-filename%
  ;; Use ID attributes as name for component HTML files?
  #t)

(define %graphic-extensions%
  ;; graphic extensions allowed
  '("gif" "png" "jpg" "jpeg" "tif" "tiff" "eps" "epsf" ))

(define %graphic-default-extension% 
  "gif")

(define %section-autolabel%
  ;; For enumerated sections (1.1, 1.1.1, 1.2, etc.)
  #t)

(define (toc-depth nd)
  ;; more depth (2 levels) to toc; instead of flat hierarchy
  5)


(define (load-header)
	
	(make formatting-instruction data: (include-characters "header.txt") )
)

(define (load-footer)
	
	(make formatting-instruction data: (include-characters "footer.txt") )
)


(define (html-document title-sosofo body-sosofo)
  (let* (;; Let's look these up once, so that we can avoid calculating
	 ;; them over and over again.
	 (prev         (prev-chunk-element))
	 (next         (next-chunk-element))
	 (prevm        (prev-major-component-chunk-element))
	 (nextm        (next-major-component-chunk-element))
	 (navlist      (list prev next prevm nextm))

	 ;; Let's make it possible to control the output even in the
	 ;; nochunks case. Note: in the nochunks case, (chunk?) will
	 ;; return #t for only the root element.
	 (make-entity? (and (or (not nochunks) rootchunk)
			    (chunk?)))

	 (make-head?   (or make-entity?
			   (and nochunks
				(node-list=? (current-node)
					     (sgml-root-element)))))
	 (doc-sosofo 
	  (if make-head?
	      (make element gi: "HTML"
		    (make element gi: "HEAD"
			  (make element gi: "TITLE" title-sosofo)
			  ($standard-html-header$ prev next prevm nextm))
		    (make element gi: "BODY"
			  attributes: (append
				       (list (list "CLASS" (gi)))
				       %body-attr%)
			  (load-header)
			  (header-navigation (current-node) navlist)
			  body-sosofo
			  (footer-navigation (current-node) navlist)
			  (load-footer) ) )
			  
	      body-sosofo)))
    (if make-entity?
	(make entity
	  system-id: (html-entity-file (html-file))
	  (if %html-pubid%
	      (make document-type
		name: "HTML"
		public-id: %html-pubid%)
	      (empty-sosofo))
	  doc-sosofo)
	(if (node-list=? (current-node) (sgml-root-element))
	    (make sequence
	      (if %html-pubid%
		  (make document-type
		    name: "HTML"
		    public-id: %html-pubid%)
		  (empty-sosofo))
	      doc-sosofo)
	    doc-sosofo))))




(element emphasis
  ;; make role=strong equate to bold for emphasis tag
  (if (equal? (attribute-string "role") "strong")
     (make element gi: "STRONG" (process-children))
     (make element gi: "EM" (process-children))))

(define (book-titlepage-recto-elements)
  ;; elements on a book's titlepage
  (list (normalize "title")
        (normalize "subtitle")
        (normalize "graphic")
        (normalize "mediaobject")
        (normalize "corpauthor")
        (normalize "authorgroup")
        (normalize "author")
        (normalize "othercredit")
        (normalize "edition")
        (normalize "releaseinfo")
        (normalize "publisher")
        (normalize "editor")
        (normalize "copyright")
        (normalize "pubdate")
        (normalize "revhistory")
        (normalize "abstract")
        (normalize "legalnotice")))

(define (article-titlepage-recto-elements)
  ;; elements on an article's titlepage
  (list (normalize "title")
        (normalize "subtitle")
        (normalize "authorgroup")
        (normalize "author")
        (normalize "othercredit")
        (normalize "releaseinfo")
        (normalize "copyright")
        (normalize "pubdate")
        (normalize "revhistory")
        (normalize "abstract")
        (normalize "legalnotice")))

(define (process-contrib #!optional (sosofo (process-children)))
  ;; print out with othercredit information; for translators, etc.
  (make sequence
    (make element gi: "SPAN"
          attributes: (list (list "CLASS" (gi)))
          (process-children))))

(define (process-othercredit #!optional (sosofo (process-children)))
  ;; print out othercredit information; for translators, etc.
  (let ((author-name  (author-string))
        (author-contrib (select-elements (children (current-node))
                                          (normalize "contrib"))))
    (make element gi: "P"
         attributes: (list (list "CLASS" (gi)))
         (make element gi: "B"
              (literal author-name)
              (literal " - "))
         (process-node-list author-contrib))))

(mode article-titlepage-recto-mode
  (element contrib (process-contrib))
  (element othercredit (process-othercredit))
)

(mode book-titlepage-recto-mode
  (element contrib (process-contrib))
  (element othercredit (process-othercredit))
)

(define (article-title nd)
  (let* ((artchild  (children nd))
         (artheader (select-elements artchild (normalize "artheader")))
         (artinfo   (select-elements artchild (normalize "articleinfo")))
         (ahdr (if (node-list-empty? artheader)
                   artinfo
                   artheader))
         (ahtitles  (select-elements (children ahdr)
                                     (normalize "title")))
         (artitles  (select-elements artchild (normalize "title")))
         (titles    (if (node-list-empty? artitles)
                        ahtitles
                        artitles)))
    (if (node-list-empty? titles)
        ""
        (node-list-first titles))))

(mode subtitle-mode
  ;; do not print subtitle on subsequent pages
  (element subtitle (empty-sosofo)))

;; Redefinition of $verbatim-display$
;; Origin: dbverb.dsl
;; Different foreground and background colors for verbatim elements
;; Author: Philippe Martin (feloy@free.fr) 2001-04-07

(define ($verbatim-display$ indent line-numbers?)
  (let ((verbatim-element (gi))
        (content (make element gi: "PRE"
                       attributes: (list
                                    (list "CLASS" (gi)))
                       (if (or indent line-numbers?)
                           ($verbatim-line-by-line$ indent line-numbers?)
                           (process-children)))))
    (if %shade-verbatim%
        (make element gi: "TABLE"
              attributes: (shade-verbatim-attr-element verbatim-element)
              (make element gi: "TR"
                    (make element gi: "TD"
                          (make element gi: "FONT" 
                                attributes: (list
                                             (list "COLOR" (car (shade-verbatim-element-colors
                                                                 verbatim-element))))
                                content))))
        content)))

;;
;; Customize this function
;; to change the foreground and background colors
;; of the different verbatim elements
;; Return (list "foreground color" "background color")
;;
(define (shade-verbatim-element-colors element)
  (case element
    (("SYNOPSIS") (list "#000000" "#6495ED"))
    ;; ...
    ;; Add your verbatim elements here
    ;; ...
    (else (list "#000000" "#E0E0E0"))))

(define (shade-verbatim-attr-element element)
  (list
  (list "BORDER" 
	(cond
		((equal? element (normalize "SCREEN")) "1")
		(else "0")))
   (list "BGCOLOR" (car (cdr (shade-verbatim-element-colors element))))
   (list "WIDTH" ($table-width$))))

;; End of $verbatim-display$ redefinition

</style-specification-body>
</style-specification>

<external-specification id="docbook" document="docbook.dsl">

</style-sheet>

